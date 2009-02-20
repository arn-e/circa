// Copyright 2008 Andrew Fischer

#include "common_headers.h"

#include "circa.h"
#include "testing.h"

#include "branch_iterators.hpp"

namespace circa {
namespace term_pointer_iterator_tests {

void simple()
{
    Branch branch;
    Term *one = branch.eval("one = 1.0");
    Term *two = branch.eval("two = 2.0");
    Term *t = branch.eval("a = add(one,two)");

    TermExternalPointersIterator it(t);

    test_assert(it.current() == one);
    it.advance();
    test_assert(it.current() == two);
    it.advance();
    test_assert(it.current() == ADD_FUNC);
    it.advance();
    test_assert(it.current() == FLOAT_TYPE);
    it.advance();
    test_assert(it.finished());
}

void no_inputs()
{
    Branch branch;

    Term *one = branch.eval("one = 1.0");

    TermExternalPointersIterator it(one);

    test_assert(it.current()->function == VALUE_FUNCTION_GENERATOR);
    it.advance();
    test_assert(it.current() == FLOAT_TYPE);
    it.advance();
    test_assert(it.finished());
}

void nested_branch()
{
    Branch branch;

    Term *one = branch.eval("one = 1.0");
    Term *nested = branch.eval("nested = Branch()");

    as_branch(nested).outerScope = &branch;

    as_branch(nested).eval("two = 1.0");
    as_branch(nested).eval("a = add(one,two)");

    TermExternalPointersIterator it(nested);

    test_assert(it.current()->function == VALUE_FUNCTION_GENERATOR);
    it.advance();
    test_assert(it.current() == BRANCH_TYPE);
    it.advance();
    test_assert(!it.finished());

    test_assert(it.current()->function == VALUE_FUNCTION_GENERATOR);
    it.advance();
    test_assert(it.current() == FLOAT_TYPE);
    it.advance();
    test_assert(it.current() == one);
    it.advance();
    test_assert(it.current() == ADD_FUNC);
    it.advance();
    test_assert(it.current() == FLOAT_TYPE);
    it.advance();
    test_assert(it.finished());
}

void recursive_iterator()
{
    Branch branch;

    Term* a = branch.eval("a = 1");
    Term* b = branch.eval("b = 2");

    RecursiveBranchIterator it(&branch);

    test_assert(it.current() == a);
    it.advance();
    test_assert(it.current() == b);
    it.advance();
    test_assert(it.finished());

    Term* funcTerm = create_value(&branch, FUNCTION_TYPE);
    Function &func = as_function(funcTerm);

    Term* c = func.subroutineBranch.eval("c = 3");
    Term* d = func.subroutineBranch.eval("d = 4");

    Term* e = branch.eval("e = 5");

    it.reset(&branch);

    test_assert(it.current() == a);
    it.advance();
    test_assert(it.current() == b);
    it.advance();
    test_assert(it.current() == funcTerm);
    it.advance();
    test_assert(it.current() == c);
    it.advance();
    test_assert(it.current() == d);
    it.advance();
    test_assert(it.current() == e);
    it.advance();
    test_assert(it.finished());
}

void register_tests()
{
    REGISTER_TEST_CASE(term_pointer_iterator_tests::simple);
    REGISTER_TEST_CASE(term_pointer_iterator_tests::no_inputs);
    //REGISTER_TEST_CASE(term_pointer_iterator_tests::nested_branch); FIXME
    REGISTER_TEST_CASE(term_pointer_iterator_tests::recursive_iterator);
}

}
} // namespace circa
