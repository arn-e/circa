// Copyright (c) Andrew Fischer. See LICENSE file for license terms.

#include "common_headers.h"

#include "block.h"
#include "building.h"
#include "code_iterators.h"
#include "kernel.h"
#include "function.h"
#include "heap_debugging.h"
#include "inspection.h"
#include "interpreter.h"
#include "names.h"
#include "string_type.h"
#include "term.h"
#include "term_list.h"
#include "type.h"

namespace circa {

bool is_actually_using(Term* user, Term* usee)
{
    for (int i=0; i < user->numDependencies(); i++)
        if (user->dependency(i) == usee)
            return true;

    return false;
}

int user_count(Term* term)
{
    return term->users.length();
}

Type* declared_type(Term* term)
{
    if (term->type == NULL)
        return NULL;
    return term->type;
}

void set_is_statement(Term* term, bool value)
{
    term->setBoolProp("statement", value);
}

bool is_statement(Term* term)
{
    return term->boolProp("statement", false);
}

bool is_comment(Term* term)
{
    return term->function == FUNCS.comment;
}

bool is_empty_comment(Term* term)
{
    return is_comment(term) && term->stringProp("comment","") == "";
}

bool is_value(Term* term)
{
    return term->function == FUNCS.value;
}

bool is_hidden(Term* term)
{
    if (term->boolProp("syntax:hidden", false))
        return true;

    if (term->name == "")
        return false;

    if (term->name[0] == '#' && term->name != "#return")
        return true;

    return false;
}

bool has_empty_name(Term* term)
{
    return is_null(&term->nameValue) || string_eq(&term->nameValue, "");
}

bool is_copying_call(Term* term)
{
    return term->function == FUNCS.output
        || term->function == FUNCS.copy;
}

bool is_an_unknown_identifier(Term* term)
{
    return term->function == FUNCS.unknown_identifier;
}

bool is_major_block(Block* block)
{
    if (block->owningTerm == NULL)
        return true;

    return is_function(block->owningTerm);
}

bool is_minor_block(Block* block)
{
    if (block->owningTerm == NULL)
        return false;
    
    Term* owner = block->owningTerm;
    return owner->function == FUNCS.if_block
        || owner->function == FUNCS.case_func
        || owner->function == FUNCS.for_func;
}

bool is_for_loop(Block* block)
{
    if (block->owningTerm == NULL)
        return false;
    if (FUNCS.for_func == NULL)
        return false;
    return block->owningTerm->function == FUNCS.for_func;
}

int get_locals_count(Block* block)
{
    return block->length();
}

Term* get_input_placeholder(Block* block, int index)
{
    if (index >= block->length())
        return NULL;
    Term* term = block->get(index);
    if (term == NULL || term->function != FUNCS.input)
        return NULL;
    return term;
}

Term* get_effective_input_placeholder(Block* block, int inputIndex)
{
    if (has_variable_args(block))
        return get_input_placeholder(block, 0);
    else
        return get_input_placeholder(block, inputIndex);
}

Term* get_output_placeholder(Block* block, int index)
{
    if (index >= block->length())
        return NULL;
    Term* term = block->getFromEnd(index);
    if (term == NULL || term->function != FUNCS.output)
        return NULL;
    return term;
}

int count_input_placeholders(Block* block)
{
    int result = 0;
    while (get_input_placeholder(block, result) != NULL)
        result++;
    return result;
}
int count_output_placeholders(Block* block)
{
    int result = 0;
    while (get_output_placeholder(block, result) != NULL)
        result++;
    return result;
}
int input_placeholder_index(Term* inputPlaceholder)
{
    return inputPlaceholder->index;
}
bool is_input_placeholder(Term* term)
{
    return term->function == FUNCS.input;
}
bool is_output_placeholder(Term* term)
{
    return term->function == FUNCS.output;
}

Term* get_output_term(Term* term, int index)
{
    if (index == 0)
        return term;
    else
        return get_extra_output(term, index - 1);
}

Term* get_extra_output(Term* term, int index)
{
    Term* position = term->owningBlock->getSafe(term->index + index + 1);
    if (position != NULL && position->function == FUNCS.extra_output)
        return position;
    return NULL;
}

Term* find_extra_output_for_state(Term* term)
{
    for (int i=0;; i++) {
        Term* extra_output = get_extra_output(term, i);
        if (extra_output == NULL)
            break;

        if (extra_output->boolProp("state", false))
            return extra_output;
    }
    return NULL;
}

bool term_is_state_input(Term* term, int index)
{
    if (index >= term->numInputs())
        return false;
    caValue* prop = term->inputInfo(index)->properties.get("state");
    if (prop == NULL)
        return false;
    return as_bool(prop);
}

Term* find_state_input(Block* block)
{
    for (int i=0;; i++) {
        Term* placeholder = get_input_placeholder(block, i);
        if (placeholder == NULL)
            return NULL;
        if (is_state_input(placeholder))
            return placeholder;
    }
}

bool has_state_input(Block* block)
{
    return find_state_input(block) != NULL;
}

Term* find_state_output(Block* block)
{
    for (int i=0;; i++) {
        Term* placeholder = get_output_placeholder(block, i);
        if (placeholder == NULL)
            return NULL;
        if (is_state_output(placeholder))
            return placeholder;
    }
}
bool has_state_output(Block* block)
{
    return find_state_output(block) != NULL;
}
bool is_state_input(Term* placeholder)
{
    return placeholder->boolProp("state", false);
}
bool is_state_output(Term* placeholder)
{
    return placeholder->boolProp("state", false);
}
bool is_input_meta(Block* block, int index)
{
    Term* placeholder = get_input_placeholder(block, index);
    if (placeholder == NULL)
        return false;
    return placeholder->boolProp("meta", false);
}

Block* term_get_function_details(Term* call)
{
    // TODO: Shouldn't need to special case these functions.
    if (call->function == FUNCS.if_block
        || call->function == FUNCS.for_func
        || call->function == FUNCS.include_func)
        return nested_contents(call);

    if (call->function == NULL)
        return NULL;

    // Check if the function is a type. (deprecated).
    if (is_type(call->function))
        return function_contents(FUNCS.cast);

    caValue* value = term_value(call->function);
    if (!is_function(value))
        return NULL;

    return function_get_contents(as_function(value));
}

Term* term_get_input_placeholder(Term* call, int index)
{
    if (!is_function(call->function))
        return NULL;

    Block* contents = term_get_function_details(call);
    if (contents == NULL)
        return NULL;
    if (index >= contents->length())
        return NULL;
    Term* term = contents->get(index);
    if (term->function != FUNCS.input)
        return NULL;
    return term;
}

int term_count_input_placeholders(Term* term)
{
    int result = 0;
    while (term_get_input_placeholder(term, result) != NULL)
        result++;
    return result;
}

Term* term_get_output_placeholder(Term* call, int index)
{
    if (!is_function(call->function))
        return NULL;

    Block* contents = term_get_function_details(call);
    if (contents == NULL)
        return NULL;
    if (index >= contents->length())
        return NULL;
    Term* term = contents->getFromEnd(index);
    if (term->function != FUNCS.output)
        return NULL;
    return term;
}
bool term_has_variable_args(Term* term)
{
    return has_variable_args(term_get_function_details(term));
}

int count_actual_output_terms(Term* term)
{
    int count = 0;
    while (get_extra_output(term, count) != NULL)
        count++;
    return count + 1;
}

Term* preceding_term(Term* term)
{
    return term->owningBlock->getSafe(term->index - 1);
}
Term* following_term(Term* term)
{
    return term->owningBlock->getSafe(term->index + 1);
}

bool has_variable_args(Block* block)
{
    for (int i=0;; i++) {
        Term* placeholder = get_input_placeholder(block, i);
        if (placeholder == NULL)
            return false;
        if (placeholder->boolProp("multiple", false))
            return true;
    }
}

Term* find_last_non_comment_expression(Block* block)
{
    for (int i = block->length() - 1; i >= 0; i--) {
        if (block->get(i) == NULL)
            continue;

        // Skip certain special functions
        Term* func = block->get(i)->function;
        if (func == FUNCS.output
                || func == FUNCS.input 
                || func == FUNCS.pack_state
                || func == FUNCS.pack_state_list_n)
            continue;

        if (block->get(i)->name == "#outer_rebinds")
            continue;
        if (block->get(i)->function != FUNCS.comment)
            return block->get(i);
    }
    return NULL;
}

Term* find_term_with_function(Block* block, Term* func)
{
    for (int i=0; i < block->length(); i++) {
        Term* term = block->getFromEnd(i);
        if (term == NULL)
            continue;
        if (term->function == func)
            return term;
    }
    return NULL;
}

Term* find_input_placeholder_with_name(Block* block, caValue* name)
{
    for (int i=0;; i++) {
        Term* placeholder = get_input_placeholder(block, i);
        if (placeholder == NULL)
            return NULL;
        if (equals(&placeholder->nameValue, name))
            return placeholder;
    }
}

Term* find_input_with_function(Term* target, Term* func)
{
    for (int i=0; i < target->numInputs(); i++) {
        Term* input = target->input(i);
        if (input == NULL) continue;
        if (input->function == func)
            return input;
    }
    return NULL;
}

Term* find_user_with_function(Term* target, Term* func)
{
    for (int i=0; i < target->users.length(); i++)
        if (target->users[i]->function == func)
            return target->users[i];
    return NULL;
}

Term* find_parent_term_in_block(Term* term, Block* block)
{
    while (true) {
        if (term == NULL)
            return NULL;

        if (term->owningBlock == block)
            return term;

        term = get_parent_term(term);
    }
}

bool has_an_error_listener(Term* term)
{
    for (int i=0; i < term->users.length(); i++) {
        if (term->users[i] && term->users[i]->function == FUNCS.errored)
            return true;
    }
    return false;
}

std::string global_id(Term* term)
{
    if (term == NULL)
        return "NULL";

    std::stringstream out;
    out << "#" << term->id;
    return out.str();
}

const char* unique_name(Term* term)
{
    return term->uniqueName.name.c_str();
}

std::string get_short_local_name(Term* term)
{
    if (term == NULL)
        return "NULL";
    if (term->name != "")
        return term->name;

    return global_id(term);
}

std::string block_namespace_to_string(Block* block)
{
    std::stringstream out;

    TermNamespace::iterator it;
    for (it = block->names.begin(); it != block->names.end(); ++it)
        out << it->first << ": " << global_id(it->second) << "\n";

    return out.str();
}

void print_block(Block* block, RawOutputPrefs* prefs, std::ostream& out)
{
    int prevIndent = prefs->indentLevel;

    out << "[Block#" << block->id << "]" << std::endl;
    for (BlockIterator it(block); !it.finished(); it.advance()) {
        Term* term = it.current();

        int indent = it.depth();

        prefs->indentLevel = indent;

        print_term(term, prefs, out);
        out << std::endl;

        // Possibly print the closing bytecode op.
        if (prefs->showBytecode
                && term->index == (term->owningBlock->length() - 1)
                && term->owningBlock != NULL
                && !is_null(&term->owningBlock->bytecode)
                ) {

            Block* nested = term->owningBlock;

            for (int i=0; i < prefs->indentLevel; i++)
                out << " ";

            out << to_string(list_get(&nested->bytecode, nested->length())) << std::endl;
        }
    }

    prefs->indentLevel = prevIndent;
}

std::string get_block_raw(Block* block)
{
    RawOutputPrefs prefs;
    std::stringstream out;
    print_block(block, &prefs, out);
    return out.str();
}

std::string get_short_location(Term* term)
{
    std::stringstream out;
    out << "[";
    std::string filename = get_source_filename(term);
    if (filename != "")
        out << filename << ":";
    if (term->sourceLoc.defined())
        out << term->sourceLoc.line << "," << term->sourceLoc.col;
    else
        out << global_id(term);

    //out << " ";
    //out << global_id(term);

    out << "]";
    return out.str();
}

std::string get_source_filename(Term* term)
{
    if (term->owningBlock == NULL)
        return "";

    Block* block = term->owningBlock;

    while (block != NULL) {
        caValue* filename = block_get_source_filename(block);

        if (filename != NULL)
            return as_string(filename);

        block = get_parent_block(block);
    }

    return "";
}

TermList get_involved_terms(TermList inputs, TermList outputs)
{
    std::vector<TermList> stack;

    // Step 1, search upwards from outputs. Maintain a stack of searched terms
    stack.push_back(outputs);
    TermList searched = outputs;

    while (!stack.back().empty()) {
        TermList &top = stack.back();

        TermList new_layer;

        for (int i=0; i < top.length(); i++) {
            for (int input_i=0; input_i < top[i]->numInputs(); input_i++) {
                Term* input = top[i]->input(input_i);
                
                if (searched.contains(input))
                    continue;

                if (inputs.contains(input))
                    continue;

                new_layer.append(input);
            }
        }

        stack.push_back(new_layer);
    }

    TermList result;
    result.appendAll(inputs);

    // Step 2, descend down our stack, and append any descendents of things
    // inside 'results'
    while (!stack.empty()) {
        TermList &layer = stack.back();

        for (int i=0; i < layer.length(); i++) {
            Term* term = layer[i];
            for (int input_i=0; input_i < term->numInputs(); input_i++) {
                Term* input = term->input(input_i);

                if (result.contains(input))
                    result.append(term);
            }
        }

        stack.pop_back();
    }

    return result;
}

void list_names_that_this_block_rebinds(Block* block, std::vector<std::string> &names)
{
    TermNamespace::iterator it;
    for (it = block->names.begin(); it != block->names.end(); ++it) {
        std::string name = it->first;

        // Ignore compiler-generated terms
        if (name[0] == '#')
            continue;

        // Ignore names that aren't bound in the outer block
        Term* outer = find_name(get_outer_scope(block), name.c_str());

        if (outer == NULL)
            continue;

        // Ignore global terms
        if (outer->owningBlock == global_root_block())
            continue;

        // Ignore terms that are just a simple copy
        Term* result = block->get(name);
        if (result->function == FUNCS.copy && result->input(0) == outer)
            continue;

        names.push_back(name);
    }
}

void print_term(Term* term, RawOutputPrefs* prefs, std::ostream& out)
{
    for (int i=0; i < prefs->indentLevel; i++)
        out << " ";

    if (term == NULL) {
        out << "<NULL>";
        return;
    }

    out << global_id(term);

    out << " " << unique_name(term);

    if (term->name != "")
        out << " '" << term->name << "'";

    if (term->function == NULL) {
        out << " <NULL function>";
    } else {
        out << " " << term->function->name;
        out << global_id(term->function);
    }

    // Arguments
    out << "(";
    for (int i=0; i < term->numInputs(); i++) {
        if (i != 0) out << " ";
        out << global_id(term->input(i));

        if (prefs->showProperties) {
            out << " ";
            out << term->inputInfo(i)->properties.toString();
        }
    }
    out << ") ";

    // Print out certain properties
    if (term->boolProp("multiple", false))
        out << ":multiple ";
    if (term->boolProp("output", false))
        out << ":output ";
    if (term->boolProp("state", false))
        out << ":state ";
    if (term->hasProperty("field"))
        out << ":field(" << term->stringProp("field", "") << ")";

    out << "t:";
    
    if (term->type == NULL)
        out << "<NULL type>";
    else
        out << as_cstring(&term->type->name);

    if (is_value(term))
        out << " val:" << to_string(term_value(term));

    if (prefs->showProperties)
        out << " " << term->properties.toString();

    if (prefs->showBytecode) {
        out << std::endl;
        for (int i=0; i < prefs->indentLevel + 2; i++)
            out << " ";

        Block* block = term->owningBlock;
        caValue* op = list_get_safe(&block->bytecode, term->index);
        if (op == NULL)
            out << "(missing bytecode)";
        else
            out << to_string(op);
    }
}

void print_term(Term* term, std::ostream& out)
{
    RawOutputPrefs prefs;
    print_term(term, &prefs, out);
}

void print_block(Block* block, std::ostream& out)
{
    RawOutputPrefs prefs;
    print_block(block, &prefs, out);
}

void print_block_with_properties(Block* block, std::ostream& out)
{
    RawOutputPrefs prefs;
    prefs.showProperties = true;
    print_block(block, &prefs, out);
}

std::string get_term_to_string_extended(Term* term)
{
    RawOutputPrefs prefs;
    std::stringstream out;
    print_term(term, &prefs, out);
    return out.str();
}

std::string get_term_to_string_extended_with_props(Term* term)
{
    RawOutputPrefs prefs;
    prefs.showProperties = true;
    std::stringstream out;
    print_term(term, &prefs, out);
    return out.str();
}

void visit_name_accessible_terms(Term* location, NamedTermVisitor visitor, caValue* context)
{
    if (location->owningBlock == NULL)
        return;

    Block* block = location->owningBlock;

    // Iterate upwards through all the terms that are above 'location' in this block
    for (int index=location->index - 1; index >= 0; index--) {
        Term* t = block->get(index);
        if (t == NULL) continue;
        if (t->name == "") continue;
        bool stop = visitor(t, t->name.c_str(), context);
        if (stop) return;

        // TODO: Iterate inside namespaces, providing the correct name
    }

    if (block->owningTerm != NULL)
        visit_name_accessible_terms(block->owningTerm, visitor, context);
}

}

