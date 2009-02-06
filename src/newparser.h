// Copyright 2008 Andrew Fischer

#include "common_headers.h"

namespace circa {
namespace newparser {

typedef Term* (*ParsingStep)(Branch& branch, TokenStream& tokens);

Term* compile(Branch& branch, ParsingStep step, std::string const& input);

Term* compile_statement(Branch& branch, std::string const& input);
Term* evaluate_statement(Branch& branch, std::string const& input);

// Parsing steps:
Term* statement_list(Branch& branch, TokenStream& tokens);
Term* statement(Branch& branch, TokenStream& tokens);
Term* comment_statement(Branch& branch, TokenStream& tokens);
Term* blank_line(Branch& branch, TokenStream& tokens);
Term* function_decl(Branch& branch, TokenStream& tokens);
Term* type_decl(Branch& branch, TokenStream& tokens);
Term* if_block(Branch& branch, TokenStream& tokens);
Term* stateful_value_decl(Branch& branch, TokenStream& tokens);
Term* expression_statement(Branch& branch, TokenStream& tokens);
Term* return_statement(Branch& branch, TokenStream& tokens);
Term* infix_expression(Branch& branch, TokenStream& tokens);
Term* infix_expression_nested(Branch& branch, TokenStream& tokens, int precedence);
Term* atom(Branch& branch, TokenStream& tokens);
Term* function_call(Branch& branch, TokenStream& tokens);
Term* literal_integer(Branch& branch, TokenStream& tokens);
Term* literal_hex(Branch& branch, TokenStream& tokens);
Term* literal_float(Branch& branch, TokenStream& tokens);
Term* literal_string(Branch& branch, TokenStream& tokens);
Term* identifier(Branch& branch, TokenStream& tokens);
std::string possible_whitespace(TokenStream& tokens);
std::string possible_newline(TokenStream& tokens);
std::string possible_whitespace_or_newline(TokenStream& tokens);

} // namespace newparser
} // namespace circa
