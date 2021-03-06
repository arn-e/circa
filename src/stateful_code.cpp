// Copyright (c) Andrew Fischer. See LICENSE file for license terms.

#include "common_headers.h"

#include "block.h"
#include "building.h"
#include "control_flow.h"
#include "kernel.h"
#include "function.h"
#include "if_block.h"
#include "inspection.h"
#include "source_repro.h"
#include "stateful_code.h"
#include "names.h"
#include "term.h"
#include "type.h"

namespace circa {

static void get_list_of_state_outputs(Block* block, int position, TermList* output);
static Term* append_final_pack_state(Block* block);

bool is_declared_state(Term* term)
{
    return term->function == FUNCS.declared_state;
}

bool is_function_stateful(Term* func)
{
    if (!is_function(func))
        return false;
    Function* attrs = as_function(func);
    if (attrs == NULL)
        return false;

    Block* block = function_contents(func);
    return has_state_input(block);
}

void pack_any_open_state_vars(Block* block)
{
    for (int i=0; i < block->length(); i++) {
        Term* term = block->get(i);
        if (term == NULL)
            continue;
        if (term->function == FUNCS.declared_state) {
            Term* result = block->get(term->name);

            // If this result already has a pack_state() term then leave it alone.
            if (find_user_with_function(result, FUNCS.pack_state) != NULL)
                continue;

            Term* pack = apply(block, FUNCS.pack_state, TermList(
                find_open_state_result(block, block->length()), result, term));
            pack->setStringProp("field", unique_name(term));
            block->move(pack, result->index + 1);
        }
    }
}

bool block_state_type_is_out_of_date(Block* block)
{
    // Alloc an array that tracks, for each field in the existing stateType,
    // whether we have found a corresponding term for that field.
    bool* typeFieldFound = NULL;
    int existingFieldCount = 0;

    if (block->stateType != NULL) {
        existingFieldCount = compound_type_get_field_count(block->stateType);
        size_t size = sizeof(bool) * existingFieldCount;
        typeFieldFound = (bool*) malloc(size);
        memset(typeFieldFound, 0, size);
    }
    
    // Walk through every term and check whether every unpack_state call is already
    // mentioned in the state type.
    for (int i=0; i < block->length(); i++) {
        Term* term = block->get(i);
        if (term == NULL)
            continue;

        if (term->function != FUNCS.unpack_state)
            continue;

        // Found an unpack_state call
        Term* identifyingTerm = term->input(1);

        // If the block doesn't yet have a stateType then that's an update.
        if (block->stateType == NULL)
            goto return_true;

        // Look for the field name
        int fieldIndex = list_find_field_index_by_name(block->stateType,
            unique_name(identifyingTerm));

        // If the name isn't found then that's an update
        if (fieldIndex == -1)
            goto return_true;

        // If the type doesn't match then that's an update
        if (compound_type_get_field_type(block->stateType, fieldIndex)
                != declared_type(term))
            goto return_true;

        // Record this field index as 'found'
        typeFieldFound[fieldIndex] = true;
    }

    // If there were any fields in the type that weren't found in the block, then
    // that's an update.
    if (typeFieldFound != NULL) {
        for (int i=0; i < existingFieldCount; i++) {
            if (!typeFieldFound[i])
                goto return_true;
        }
    }

    // No reason to update, return false.
    free(typeFieldFound);
    return false;

return_true:
    free(typeFieldFound);
    return true;
}

void block_update_state_type(Block* block)
{
    if (block_state_type_is_out_of_date(block)) {

        // TODO: Handle the case where the stateType should go from non-NULL to NULL

        // Recreate the state type
        Type* type = create_compound_type();

        // TODO: give this new type a nice name

        for (int i=0; i < block->length(); i++) {
            Term* term = block->get(i);
            if (term == NULL)
                continue;

            if (term->function != FUNCS.unpack_state || FUNCS.unpack_state == NULL)
                continue;

            Term* identifyingTerm = term->input(1);

            compound_type_append_field(type, declared_type(term), unique_name(identifyingTerm));
        }

        block->stateType = type;

        // Might need to update any existing pack_state calls.
        block_update_existing_pack_state_calls(block);
    }
}

static Term* append_final_pack_state(Block* block)
{
    TermList inputs;
    get_list_of_state_outputs(block, block->length(), &inputs);
    Term* term = apply(block, FUNCS.pack_state, inputs);
    term->setBoolProp("final", true);
    return term;
}

// For the given field name
static Term* find_output_term_for_state_field(Block* block, const char* fieldName, int position)
{
    Term* result = find_from_unique_name(block, fieldName);

    // For declared state, the result is the last term with the given name
    if (result->function == FUNCS.declared_state) {
        return find_local_name(block, result->name.c_str(), position);
    }

    ca_assert(result != NULL);

    // This term might be the actual state result, or the state result might be
    // found in an extra output. Look around and see if this term has a stateful
    // extra output.
    for (int outputIndex=0;; outputIndex++) {
        Term* extraOutput = get_extra_output(result, outputIndex);
        if (extraOutput == NULL)
            break;

        if (is_state_output(extraOutput))
            return extraOutput;
    }

    return result;
}

// Write a list of terms to 'output' corresponding to the list of state outputs at this
// position in the block. Useful for populating a list of inputs for pack_state.
static void get_list_of_state_outputs(Block* block, int position, TermList* output)
{
    output->clear();

    if (block->stateType == NULL)
        return;

    for (int i=0; i < compound_type_get_field_count(block->stateType); i++) {

        const char* fieldName = compound_type_get_field_name(block->stateType, i);
        Term* result = find_output_term_for_state_field(block, fieldName, position);
        output->append(result);
    }
}

void block_update_existing_pack_state_calls(Block* block)
{
    if (block->stateType == NULL) {
        // No state type, make sure there's no pack_state call.
        // TODO: Handle this case properly (should search and destroy an existing pack_state call)
        return;
    }

    int stateOutputIndex = block->length() - 1 - find_state_output(block)->index;

    for (int i=0; i < block->length(); i++) {
        Term* term = block->get(i);
        if (term == NULL)
            continue;

        if (term->function == FUNCS.pack_state) {
            // Update the inputs for this pack_state call
            TermList inputs;
            get_list_of_state_outputs(block, i, &inputs);

            set_inputs(term, inputs);
        }

        if (is_exit_point(term)) {
            // Check if we need to insert a pack_state call
            Term* existing = term->input(stateOutputIndex);

            if (existing == NULL || existing->function != FUNCS.pack_state) {
                TermList inputs;
                get_list_of_state_outputs(block, i, &inputs);
                if (inputs.length() != 0) {
                    Term* pack_state = apply(block, FUNCS.pack_state, inputs);
                    move_before(pack_state, term);
                    set_input(term, stateOutputIndex + 1, pack_state);

                    // Advance i to compensate for the term just added
                    i++;
                }
            }
        }
    }
}

Term* find_active_state_container(Block* block)
{
    // Check if there is already a stateful input

    // Special case for if-block: Look for a unpack_state_from_list call
    if (is_case_block(block)) {
        Term* existing = find_term_with_function(block, FUNCS.unpack_state_from_list);
        if (existing != NULL)
            return existing;
    }

    // Special case for for-block: Look for a unpack_state_from_list call

    Term* existing = find_state_input(block);
    if (existing != NULL)
        return existing;

    return NULL;
}

Term* find_or_create_state_container(Block* block)
{
    Term* existing = find_active_state_container(block);
    if (existing != NULL)
        return existing;

    // None yet, insert one
    Term* input = append_state_input(block);

    // Add a final pack_state call too
    append_final_pack_state(block);

    // And the state output
    append_state_output(block);

    return input;
}

Term* block_add_pack_state(Block* block)
{
    TermList inputs;
    get_list_of_state_outputs(block, block->length(), &inputs);

    // Don't create anything if there are no state outputs
    if (inputs.length() == 0)
        return NULL;

    return apply(block, FUNCS.pack_state, inputs);
}

// Unpack a state value. Input 1 is the "identifying term" which is used as a key.
void unpack_state(caStack* stack)
{
    caValue* container = circa_input(stack, 0);
    Term* identifyingTerm = (Term*) circa_caller_input_term(stack, 1);

    if (identifyingTerm == NULL)
        return circa_output_error(stack, "input 1 is NULL");

    caValue* element = get_field(container, unique_name(identifyingTerm));

    if (element == NULL) {
        set_null(circa_output(stack, 0));
    } else {
        copy(element, circa_output(stack, 0));
    }
}

// Pack a state value. Each input will correspond with a slot in the block's state type.
void pack_state(caStack* stack)
{
    Term* caller = (Term*) circa_caller_term(stack);
    Block* block = caller->owningBlock;

    if (block->stateType == NULL)
        return;

    caValue* args = circa_input(stack, 0);
    caValue* output = circa_output(stack, 0);
    make(block->stateType, output);

    for (int i=0; i < circa_count(args); i++) {
        caValue* input = circa_index(args, i);
        caValue* dest = list_get(output, i);
        if (input == NULL)
            set_null(dest);
        else
            copy(input, dest);
    }
}

} // namespace circa
