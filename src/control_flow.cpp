// Copyright (c) Andrew Fischer. See LICENSE file for license terms.

#include "common_headers.h"

#include "block.h"
#include "building.h"
#include "code_iterators.h"
#include "control_flow.h"
#include "inspection.h"
#include "interpreter.h"
#include "function.h"
#include "if_block.h"
#include "importing.h"
#include "inspection.h"
#include "kernel.h"
#include "source_repro.h"
#include "string_type.h"
#include "term.h"

namespace circa {

static Symbol max_exit_level(Symbol left, Symbol right);
static void update_inputs_for_exit_point(Term* exitCall, Term* exitPoint);
static void create_implicit_outputs_for_exit_point(Term* exitCall, Term* exitPoint);

bool is_exit_point(Term* term)
{
    return term->function == FUNCS.return_func
        || term->function == FUNCS.break_func
        || term->function == FUNCS.continue_func
        || term->function == FUNCS.discard;
}

Symbol term_get_highest_exit_level(Term* term)
{
    if (term->function == FUNCS.return_func)
        return sym_ExitLevelFunction;
    else if (term->function == FUNCS.break_func
            || term->function == FUNCS.continue_func
            || term->function == FUNCS.discard)
        return sym_ExitLevelLoop;
    else
        return sym_None;
}

static Symbol max_exit_level(Symbol left, Symbol right)
{
    if (left == sym_ExitLevelFunction || right == sym_ExitLevelFunction)
        return sym_ExitLevelFunction;
    if (left == sym_ExitLevelLoop || right == sym_ExitLevelLoop)
        return sym_ExitLevelLoop;
    return sym_None;
}

void break_formatSource(caValue* source, Term* term)
{
    append_phrase(source, "break", term, sym_Keyword);
}
void continue_formatSource(caValue* source, Term* term)
{
    append_phrase(source, "continue", term, sym_Keyword);
}
void discard_formatSource(caValue* source, Term* term)
{
    append_phrase(source, "discard", term, sym_Keyword);
}

void return_formatSource(caValue* source, Term* term)
{
    if (term->boolProp("syntax:returnStatement", false)) {
        append_phrase(source, "return", term, sym_Keyword);
        append_phrase(source,
                term->stringProp("syntax:postKeywordWs", " "),
                term, sym_Whitespace);

        for (int inputIndex=0; inputIndex < term->numInputs(); inputIndex++) {
            if (inputIndex != 0)
                append_phrase(source, ", ", term, sym_None);
            format_source_for_input(source, term, inputIndex, "", "");
        }
    } else {
        format_term_source_default_formatting(source, term);
    }
}

Term* find_output_placeholder_for_intermediate_term(Term* term)
{
    // TODO
    return NULL;
}

void create_output_from_minor_block(Block* block, caValue* description)
{
    if (is_case_block(block)) {
        Block* ifBlock = get_block_for_case_block(block);
        if_block_append_output(ifBlock, description);
    } else if (is_minor_block(block)) {
        append_output_placeholder_with_description(block, description);
    }
}

void create_block_output_for_term(Term* term)
{
#if 0
    Block* block = term->owningBlock;

    // If this term is inside an if-block, then add it as a block output.
    if (is_case_block(block)) {
        Block* ifBlock = get_block_for_case_block(block);
        Term* existing = if_block_get_output_by_name(ifBlock, term->name.c_str());
        if (existing == NULL) {
            if_block_append_output(ifBlock, term->name.c_str());
        } else {
            // Connect to existing output
            set_input(find_output_placeholder_with_name(block, term->name.c_str()), 0, term);
        }
    } else if (is_minor_block(block)) {

        Term* existing = find_output_placeholder_with_name(block, term->name.c_str());
        if (existing == NULL) {
            Term* placeholder = append_output_placeholder(block, term);
            rename(placeholder, term->nameSymbol);
        }
    }
#endif
}

Symbol term_get_escaping_exit_level(Term* term)
{
    // Check for a call that directly causes exit: return/continue/etc.
    Symbol directExitLevel = term_get_highest_exit_level(term);
    if (directExitLevel != sym_None)
        return directExitLevel;

    // For-block
    if (term->function == FUNCS.for_func) {
        Block* contents = nested_contents(term);

        for (int i=0; i < contents->length(); i++) {
            Symbol exit = term_get_highest_exit_level(contents->get(i));

            // Only ExitRankFunction escapes from for-block.
            if (exit == sym_ExitLevelFunction)
                return exit;
        }

        return sym_None;
    }

    // If-block
    if (term->function == FUNCS.if_block) {
        Block* topContents = nested_contents(term);
        Symbol highestExit = sym_None;
        for (int caseIndex=0; caseIndex < topContents->length(); caseIndex++) {
            Block* caseBlock = nested_contents(topContents->get(caseIndex));
            for (int i=0; i < caseBlock->length(); i++) {

                Symbol exit = term_get_highest_exit_level(caseBlock->get(i));

                // All exits escape from if-block.
                highestExit = max_exit_level(exit, highestExit);
            }
        }
        return highestExit;
    }

    return sym_None;
}

void update_derived_inputs_for_exit_point(Block* block, Term* term)
{
    // Make sure that this exit point includes every block output as an input.
    // The intermediate value might be different at this location.
    
    for (int i=0;; i++) {
        Term* blockOutput = get_output_placeholder(block, i);
        if (blockOutput == NULL)
            break;

        // Don't touch input if it's explicit.
        if (i < term->numInputs() && !is_input_implicit(term, i))
            return;

        Term* intermediateValue = find_intermediate_result_for_output(term, blockOutput);

        set_input(term, i, intermediateValue);
        set_input_implicit(term, i, true);
        set_input_hidden(term, i, true);
    }
}

void update_for_control_flow(Block* block)
{
    if (!is_minor_block(block))
        return;

    for (int i=0; i < block->length(); i++) {
        Term* term = block->get(i);
        if (term == NULL)
            continue;
        if (!is_exit_point(term))
            continue;

        update_derived_inputs_for_exit_point(block, term);
    }
}

Term* find_intermediate_result_for_output(Term* location, Term* output)
{
    Value description;
    get_output_description(output, &description);
    caValue* descriptionTag = list_get(&description, 0);

    // Control value
    if (as_symbol(descriptionTag) == sym_Control) {
        Block* block = location->owningBlock;
        for (int i = location->index; i >= 0; i--) {
            Term* term = block->get(i);
            if (term == NULL)
                continue;
            if (term->boolProp("control", false))
                return term;
        }
        return NULL;
    }
    
    // Check whether the output's connection is valid at this location
    Term* result = output->input(0);
    if (result != NULL
            && result->owningBlock == output->owningBlock
            && result->index < location->index)
        return result;

    // State output
    if (is_state_input(output))
        return find_open_state_result(location);

    // Nearest with same name
    if (output->name != "")
        return find_name_at(location, output->name.c_str());

    return NULL;
}

static void update_inputs_for_exit_point(Term* exitCall, Term* exitPoint)
{
    // Each input to the exit_point should correspond with an output from this
    // block. Our goal is to capture the "in progress" value for each output.
    
    Block* block = exitPoint->owningBlock;

    set_inputs(exitPoint, TermList());

    for (int i=0;; i++) {

        Term* output = get_output_placeholder(block, i);
        if (output == NULL)
            break;

        // For 'return', check for outputs that are directly given as return() args.
        if (exitCall->function == FUNCS.return_func) {
            if (i < exitCall->numInputs()) {
                set_input(exitPoint, i, exitCall->input(i));
                continue;
            }
        }

        Term* intermediateValue = find_intermediate_result_for_output(exitPoint, output);
        set_input(exitPoint, i, intermediateValue);
    }
}

static void create_implicit_outputs_for_exit_point(Term* exitCall, Term* exitPoint)
{
    Block* block = exitPoint->owningBlock;

    // For a return(), make sure there are enough anonymous outputs.
    int returnOutputs = 0;
    if (exitCall->function == FUNCS.return_func)
        returnOutputs = exitCall->numInputs();

    int existingAnonOutputs = count_anonymous_outputs(block);
    for (int outputIndex = returnOutputs; outputIndex < existingAnonOutputs; outputIndex++) {
        insert_output_placeholder(block, NULL, outputIndex);
    }

    // Named outputs.
    
    // exitLevel value.
}

void control_flow_setup_funcs(Block* kernel)
{
    FUNCS.return_func = import_function(kernel, NULL, "return(any outs :multiple :optional)");
    block_set_evaluation_empty(function_contents(FUNCS.return_func), true);
    as_function(FUNCS.return_func)->formatSource = return_formatSource;

    FUNCS.discard = import_function(kernel, NULL, "discard(any outs :multiple :optional)");
    block_set_evaluation_empty(function_contents(FUNCS.discard), true);
    as_function(FUNCS.discard)->formatSource = discard_formatSource;

    FUNCS.break_func = import_function(kernel, NULL, "break(any outs :multiple :optional)");
    block_set_evaluation_empty(function_contents(FUNCS.break_func), true);
    as_function(FUNCS.break_func)->formatSource = break_formatSource;

    FUNCS.continue_func = import_function(kernel, NULL, "continue(any outs :multiple :optional)");
    block_set_evaluation_empty(function_contents(FUNCS.continue_func), true);
    as_function(FUNCS.continue_func)->formatSource = continue_formatSource;
}

} // namespace circa
