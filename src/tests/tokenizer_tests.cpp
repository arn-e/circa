// Copyright 2008 Paul Hodge

#include "common_headers.h"

#include "testing.h"
#include "branch.h"
#include "builtins.h"
#include "term.h"
#include "runtime.h"
#include "tokenizer.h"
#include "token_stream.h"

namespace token = circa::tokenizer;

namespace circa {
namespace tokenizer_tests {

void test_identifiers()
{
    token::TokenList results;
    token::tokenize("word has_underscore has_hyphen,hasnumbers183", results);

    test_assert(results.size() == 7);

    test_assert(results[0].text == "word");
    test_assert(results[0].match == token::IDENTIFIER);
    test_assert(results[1].text == " ");
    test_assert(results[1].match == token::WHITESPACE);
    test_assert(results[2].text == "has_underscore");
    test_assert(results[2].match == token::IDENTIFIER);
    test_assert(results[3].text == " ");
    test_assert(results[3].match == token::WHITESPACE);
    test_assert(results[4].text == "has_hyphen");
    test_assert(results[4].match == token::IDENTIFIER);
    test_assert(results[5].text == ",");
    test_assert(results[5].match == token::COMMA);
    test_assert(results[6].text == "hasnumbers183");
    test_assert(results[6].match == token::IDENTIFIER);
}

void test_integers()
{
    token::TokenList results;
    token::tokenize("1 0 1234567890 -3 0x123", results);

    test_assert(results.size() == 9);
    test_assert(results[0].text == "1");
    test_assert(results[0].match == token::INTEGER);
    test_assert(results[1].text == " ");
    test_assert(results[1].match == token::WHITESPACE);
    test_assert(results[2].text == "0");
    test_assert(results[2].match == token::INTEGER);
    test_assert(results[3].text == " ");
    test_assert(results[3].match == token::WHITESPACE);
    test_assert(results[4].text == "1234567890");
    test_assert(results[4].match == token::INTEGER);
    test_assert(results[5].text == " ");
    test_assert(results[5].match == token::WHITESPACE);
    test_assert(results[6].text == "-3");
    test_assert(results[6].match == token::INTEGER);
    test_assert(results[8].text == "0x123");
    test_assert(results[8].match == token::HEX_INTEGER);
}

void test_floats()
{
    token::TokenList results;
    token::tokenize("1.0 16. .483 .123. -0.1 -.54", results);

    test_assert(results[0].text == "1.0");
    test_assert(results[0].match == token::FLOAT);
    test_assert(results[2].text == "16.");
    test_assert(results[2].match == token::FLOAT);
    test_assert(results[4].text == ".483");
    test_assert(results[4].match == token::FLOAT);
    test_assert(results[6].text == ".123");
    test_assert(results[6].match == token::FLOAT);
    test_assert(results[7].text == ".");
    test_assert(results[7].match == token::DOT);
    test_assert(results[9].text == "-0.1");
    test_assert(results[9].match == token::FLOAT);
    test_assert(results[11].text == "-.54");
    test_assert(results[11].match == token::FLOAT);
    test_assert(results.size() == 12);
}

void test_symbols1()
{
    token::TokenList results;
    token::tokenize(",()=?][<=>=", results);

    test_assert(results.size() == 9);
    test_assert(results[0].text == ",");
    test_assert(results[0].match == token::COMMA);
    test_assert(results[1].text == "(");
    test_assert(results[1].match == token::LPAREN);
    test_assert(results[2].text == ")");
    test_assert(results[2].match == token::RPAREN);
    test_assert(results[3].text == "=");
    test_assert(results[3].match == token::EQUALS);
    test_assert(results[4].text == "?");
    test_assert(results[4].match == token::QUESTION);
    test_assert(results[5].text == "]");
    test_assert(results[5].match == token::RBRACKET);
    test_assert(results[6].text == "[");
    test_assert(results[6].match == token::LBRACKET);
    test_assert(results[7].text == "<=");
    test_assert(results[7].match == token::LTHANEQ);
    test_assert(results[8].text == ">=");
    test_assert(results[8].match == token::GTHANEQ);
}

void test_symbols2()
{
    token::TokenList results;
    token::tokenize("<>:;%...", results);
    std::cout << results.size();
    test_assert(results.size() == 6);
    test_assert(results[0].text == "<");
    test_assert(results[0].match == token::LTHAN);
    test_assert(results[1].text == ">");
    test_assert(results[1].match == token::GTHAN);
    test_assert(results[2].text == ":");
    test_assert(results[2].match == token::COLON);
    test_assert(results[3].text == ";");
    test_assert(results[3].match == token::SEMICOLON);
    test_assert(results[4].text == "%");
    test_assert(results[4].match == token::PERCENT);
    test_assert(results[5].text == "...");
    test_assert(results[5].match == token::ELLIPSIS);
}

void test_keywords()
{
    token::TokenList results;
    token::tokenize("end,if,else,for,state", results);

    test_assert(results.size() == 9);
    test_assert(results[0].text == "end");
    test_assert(results[0].match == token::END);
    test_assert(results[2].text == "if");
    test_assert(results[2].match == token::IF);
    test_assert(results[4].text == "else");
    test_assert(results[4].match == token::ELSE);
    test_assert(results[6].text == "for");
    test_assert(results[6].match == token::FOR);
    test_assert(results[8].text == "state");
    test_assert(results[8].match == token::STATE);
}

void test_identifiers_that_look_like_keywords()
{
    token::TokenList results;
    token::tokenize("endup,iffy,else_,stateful", results);

    test_assert(results.size() == 7);
    test_assert(results[0].text == "endup");
    test_assert(results[0].match == token::IDENTIFIER);
    test_assert(results[2].text == "iffy");
    test_assert(results[2].match == token::IDENTIFIER);
    test_assert(results[4].text == "else_");
    test_assert(results[4].match == token::IDENTIFIER);
    test_assert(results[6].text == "stateful");
    test_assert(results[6].match == token::IDENTIFIER);
}

void test_string_literal()
{
    token::TokenList results;
    token::tokenize("\"string literal\"", results);

    test_assert(results.size() == 1);
    test_assert(results[0].text == "\"string literal\"");
    test_assert(results[0].match == token::STRING);
}

void test_token_stream()
{
    TokenStream tstream("1 2.0");

    test_assert(tstream.nextIs(tokenizer::INTEGER));
    test_assert(tstream.nextIs(tokenizer::WHITESPACE, 1));
    test_assert(tstream.nextNonWhitespaceIs(tokenizer::FLOAT, 1));
}

void token_stream_to_string()
{
    TokenStream tstream("hi + 0.123");

    test_assert(tstream.toString() ==
            "{index: 0, tokens: [IDENTIFIER \"hi\", WHITESPACE \" \", + \"+\", "
            "WHITESPACE \" \", FLOAT \"0.123\"]}");
}

void register_tests()
{
    REGISTER_TEST_CASE(tokenizer_tests::test_identifiers);
    REGISTER_TEST_CASE(tokenizer_tests::test_integers);
    REGISTER_TEST_CASE(tokenizer_tests::test_floats);
    REGISTER_TEST_CASE(tokenizer_tests::test_symbols1);
    REGISTER_TEST_CASE(tokenizer_tests::test_symbols2);
    REGISTER_TEST_CASE(tokenizer_tests::test_keywords);
    REGISTER_TEST_CASE(tokenizer_tests::test_identifiers_that_look_like_keywords);
    REGISTER_TEST_CASE(tokenizer_tests::test_string_literal);
    REGISTER_TEST_CASE(tokenizer_tests::test_token_stream);
    REGISTER_TEST_CASE(tokenizer_tests::token_stream_to_string);
}

} // namespace tokenizer_tests

} // namespace circa
