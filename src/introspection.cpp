// Copyright 2008 Paul Hodge

#include "common_headers.h"

#include "circa.h"

namespace circa {

bool is_value(Term* term)
{
    assert_good_pointer(term);

    return term->function == VALUE_FUNC;
}

bool is_actually_using(Term* user, Term* usee)
{
    assert_good_pointer(user);
    assert_good_pointer(usee);

    if (user->function == usee)
        return true;

    for (unsigned int i=0; i < user->inputs.count(); i++) {
        if (user->inputs[i] == usee)
            return true;
    }

    return false;
}

std::string format_global_id(Term* term)
{
    std::stringstream out;
    out << "$" << std::hex << term->globalID;
    return out.str();
}

std::string get_short_local_name(Term* term)
{
    if (term == NULL)
        return "NULL";
    if (term->name != "")
        return term->name;

    return format_global_id(term);
}

std::string term_to_raw_string(Term* term)
{
    if (term == NULL)
        return "<NULL>";

    std::stringstream output;

    std::string name = term->name;
    std::string funcName = get_short_local_name(term->function);
    std::string typeName = term->type->name;

    output << format_global_id(term) << " ";

    if (name != "")
        output << "'" << name << "' ";

    output << funcName << "(";

    bool first_input = true;
    for (unsigned int input_index=0; input_index < term->inputs.count(); input_index++) {
        Term* input = term->inputs[input_index];
        if (!first_input) output << ", ";
        output << format_global_id(input);
        first_input = false;
    }

    output << ")";

    if (term->type != VOID_TYPE)
        output << " : " << typeName;

    bool showValue = term->value != NULL;

    if (is_branch(term))
        showValue = false;

    if (showValue)
        output << " == " << term->toString();

    return output.str();
}

std::string branch_namespace_to_string(Branch& branch)
{
    std::stringstream out;

    TermNamespace::iterator it;
    for (it = branch.names.begin(); it != branch.names.end(); ++it) {
        out << it->first << ": " << format_global_id(it->second) << "\n";
    }

    return out.str();
}

std::string branch_to_string_raw(Branch& branch)
{
    std::stringstream out;
    for (BranchIterator it(branch); !it.finished(); it.advance()) {
        Term* term = it.current();

        int indent = it.depth();

        for (int i=0; i < indent; i++) out << "  ";

        out << term_to_raw_string(term) << std::endl;
    }
    return out.str();
}

bool function_allows_term_reuse(Function &function)
{
    if (!function.pureFunction)
        return false;

    return true;
}

bool is_equivalent(Term* target, Term* function, RefList const& inputs)
{
    assert_good_pointer(target);
    assert_good_pointer(function);
    if (target->function != function)
        return false;

    if (!function_allows_term_reuse(as_function(function)))
        return false;

    // Check inputs
    unsigned int numInputs = target->inputs.count();

    if (numInputs != inputs.count())
        return false;

    for (unsigned int i=0; i < numInputs; i++) {
        if (target->inputs[i] != inputs[i]) {
            return false;
        }
    }

    return true;
}

Term* find_equivalent(Branch& branch, Term* function, RefList const& inputs)
{
    if (!function_allows_term_reuse(as_function(function))) {
        return NULL;
    }

    for (int i=0; i < branch.length(); i++) {
        if (is_equivalent(branch[i], function, inputs))
            return branch[i];
    }

    return NULL;
}

void print_runtime_errors(Branch& branch, std::ostream& output)
{
    for (int i=0; i < branch.length(); i++) {
        Term *term = branch[i];

        if (term == NULL)
            continue;

        if (term->hasError) {
            output << "error on " << term->name << ": " << term->getErrorMessage() << std::endl;
        }
    }
}

int count_compile_errors(Branch& branch)
{
    int result = 0;

    for (int i=0; i < branch.length(); i++)
        if (has_compile_error(branch[i]))
            result++;

    return result;
}

std::string get_short_location(Term* term)
{
    std::stringstream out;
    std::string filename = get_source_filename(term);
    if (filename != "")
        out << get_source_filename(term) << ":";
    if (term->hasProperty("lineStart")) out << term->intProp("lineStart");
    else out << "unknown-line";
    out << ",";
    if (term->hasProperty("colStart")) out << term->intProp("colStart");
    else out << "unknown-col";
    return out.str();
}

std::string get_source_filename(Term* term)
{
    if (term->owningBranch == NULL)
        return "";

    Branch* branch = term->owningBranch;

    while (branch != NULL) {
        if (branch->contains(get_name_for_attribute("source-file")))
            return as_string(branch->getNamed(get_name_for_attribute("source-file")));

        branch = get_outer_scope(*branch);
    }

    return "";
}

bool has_compile_error(Term* term)
{
    return ((term->function->function == UNKNOWN_FUNCTION)
        || (term->type->function == UNKNOWN_TYPE_FUNC)
        || (term->function == UNKNOWN_IDENTIFIER_FUNC)
        || (term->function == UNRECOGNIZED_EXPRESSION_FUNC));
}

std::string get_compile_error_message(Term* term)
{
    if (!has_compile_error(term))
        return "";

    std::stringstream out;

    out << get_short_location(term) << ": ";

    if (term->function->function == UNKNOWN_FUNCTION)
        out << "Unknown function: " << term->function->stringProp("message");
    else if (term->type->function == UNKNOWN_TYPE_FUNC)
        out << "Unknown type: " << term->type->stringProp("message");
    else if (term->function == UNKNOWN_IDENTIFIER_FUNC)
        out << "Unknown identifier: " << term->stringProp("message");
    else if (term->function == UNRECOGNIZED_EXPRESSION_FUNC)
        out << "Unrecognized expression: " << term->stringProp("message");

    return out.str();
}

void print_compile_errors(Branch& branch, std::ostream& output)
{
    for (int i=0; i < branch.length(); i++) {
        Term* term = branch[i];

        if (has_compile_error(term))
            output << get_compile_error_message(term) << std::endl;
    }
}

void recursive_append_influencing_values(Term* term, RefList& list)
{
    for (int i=0; i < term->numInputs(); i++) {
        Term* input = term->input(i);

        if (input == NULL)
            continue;

        if (list.contains(input))
            continue;

        if (is_value(input) || is_stateful(input))
            list.append(input);
        else
            recursive_append_influencing_values(input, list);
    }
}

RefList get_influencing_values(Term* term)
{
    RefList result;

    recursive_append_influencing_values(term, result);

    return result;
}

RefList get_involved_terms(RefList inputs, RefList outputs)
{
    std::vector<RefList> stack;

    // Step 1, search upwards from outputs. Maintain a stack of searched terms
    stack.push_back(outputs);
    RefList searched = outputs;

    while (!stack.back().empty()) {
        RefList &top = stack.back();

        RefList new_layer;

        for (unsigned int i=0; i < top.count(); i++) {
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

    RefList result;
    result.appendAll(inputs);

    // Step 2, descend down our stack, and append any descendents of things
    // inside 'results'
    while (!stack.empty()) {
        RefList &layer = stack.back();

        for (unsigned int i=0; i < layer.count(); i++) {
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

void list_names_that_this_branch_rebinds(Branch& branch, std::vector<std::string> &names)
{
    TermNamespace::iterator it;
    for (it = branch.names.begin(); it != branch.names.end(); ++it) {
        // Ignore names that aren't bound in the outer branch
        std::string name = it->first;
        Term* outer = find_named(get_outer_scope(branch), name);
        if (outer == NULL)
            continue;

        // Ignore terms that are just a simple copy
        Term* result = branch[name];
        if (result->function == COPY_FUNC && result->input(0) == outer)
            continue;

        // Ignore compiler-generated terms. This seems like a bad method
        if (name[0] == '#')
            continue;

        names.push_back(name);
    }
}

} // namespace circa
