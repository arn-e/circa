// Copyright (c) 2007-2010 Paul Hodge. All rights reserved.

#include "common_headers.h"

#include <circa.h>

namespace circa {
namespace introspection_tests {

void test_is_value()
{
    Branch branch;

    test_assert(is_value(create_value(branch, INT_TYPE)));
    test_assert(is_value(create_value(branch, STRING_TYPE)));
    test_assert(is_value(create_value(branch, BOOL_TYPE)));
    test_assert(!is_value(branch.eval("1 + 2")));
}

void test_get_involved_terms()
{
    Branch branch;

    Term* a = branch.eval("a = 1.0");
    branch.eval("b = 2.0");
    Term* c = branch.eval("c = add(a,b)");
    Term* d = branch.eval("d = add(c,5.0)");
    branch.eval("e = add(c,5.0)");

    RefList subtree = get_involved_terms(RefList(a), RefList(d));

    test_equals(subtree, RefList(a,c,d));
}

void test_term_to_raw_string()
{
    // Test that term_to_raw_string doesn't die if a term has a NULL function or type.
    Term* term = new Term();

    term_to_raw_string(term);

    delete term;
}

void register_tests()
{
    REGISTER_TEST_CASE(introspection_tests::test_is_value);
    REGISTER_TEST_CASE(introspection_tests::test_get_involved_terms);
    REGISTER_TEST_CASE(introspection_tests::test_term_to_raw_string);
}

} // namespace introspection_tests

} // namespace circa
