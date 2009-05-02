#ifndef CIRCA_PARSER_UTIL_INCLUDED
#define CIRCA_PARSER_UTIL_INCLUDED

#include "common_headers.h"

namespace circa {

namespace tokenizer { class Token; }

Term* apply_with_syntax(Branch& branch, Term* function, RefList inputs);
void prepend_whitespace(Term* term, std::string const& whitespace);
void append_whitespace(Term* term, std::string const& whitespace);
void include_location(Term* term, tokenizer::Token& tok);
Term* find_and_apply(Branch& branch, std::string const& functionName, RefList inputs);
void recursively_mark_terms_as_occuring_inside_an_expression(Term* term);
Term* find_type(Branch& branch, std::string const& name);
Term* find_function(Branch& branch, std::string const& name);
void push_pending_rebind(Branch& branch, std::string const& name);
std::string pop_pending_rebind(Branch& branch);
void remove_compilation_attrs(Branch& branch);
void wrap_up_branch(Branch& branch);
void source_set_hidden(Term* term, bool hidden);

} // namespace circa

#endif
