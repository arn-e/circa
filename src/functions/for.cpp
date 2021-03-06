// Copyright (c) Andrew Fischer. See LICENSE file for license terms.

#include "circa/internal/for_hosted_funcs.h"

namespace circa {
namespace for_function {

    void format_heading(caValue* source, Term* term)
    {
        format_name_binding(source, term);
        append_phrase(source, "for ", term, sym_Keyword);
        std::string explicitTypeName = term->stringProp("syntax:explicitType", "");
        if (explicitTypeName != "") {
            append_phrase(source, explicitTypeName, term, sym_None);
            append_phrase(source, " ", term, sym_Whitespace);
        }
        append_phrase(source, for_loop_get_iterator_name(term), term, sym_None);
        append_phrase(source, " in ", term, sym_Keyword);
        if (term->boolProp("modifyList", false))
            append_phrase(source, "@", term, sym_None);
        format_source_for_input(source, term, 0);
    }

    void formatSource(caValue* source, Term* term)
    {
        format_heading(source, term);
        format_block_source(source, nested_contents(term), term);
        append_phrase(source, term->stringProp("syntax:whitespaceBeforeEnd", ""),
            term, tok_Whitespace);
    }

    void setup(Block* kernel)
    {
        FUNCS.for_func = import_function(kernel, NULL, "for(Indexable list) -> List");
        as_function(FUNCS.for_func)->formatSource = formatSource;

        FUNCS.loop_iterator = import_function(kernel, NULL,
            "loop_iterator(any _, any _) -> int");
        FUNCS.loop_index = import_function(kernel, NULL, "loop_index(int index) -> int");
        block_set_evaluation_empty(function_contents(FUNCS.loop_index), true);

        FUNCS.loop_output_index = import_function(kernel, NULL, "loop_output_index() -> any");
        block_set_evaluation_empty(function_contents(FUNCS.loop_output_index), true);

        FUNCS.unbounded_loop = import_function(kernel, evaluate_unbounded_loop,
            "loop(bool condition)");
        FUNCS.unbounded_loop_finish = import_function(kernel, evaluate_unbounded_loop_finish,
            "unbounded_loop_finish()");
    }
}
} // namespace circa
