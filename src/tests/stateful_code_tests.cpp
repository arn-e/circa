// Copyright (c) 2007-2010 Paul Hodge. All rights reserved.

#include "common_headers.h"

#include <circa.h>

namespace circa {
namespace stateful_code_tests {

void test_get_hidden_state_for_call()
{
    Branch branch;
    branch.eval("def f() state i end");
    Term* call = branch.eval("f()");
    Term* hidden_state = branch[1];

    test_assert(is_stateful(hidden_state));
    test_assert(get_hidden_state_for_call(call) == hidden_state);
    test_assert(get_hidden_state_for_call(hidden_state) == NULL);
    test_assert(find_call_for_hidden_state(hidden_state) == call);
    test_assert(find_call_for_hidden_state(call) == NULL);
}

void test_simple()
{
    Branch branch;
    Term* i = branch.eval("state int i");
    test_assert(is_stateful(i));
    test_assert(i->type == INT_TYPE);

    Term* j = branch.eval("state i = 0");
    test_assert(is_stateful(j));
    test_assert(j->type == INT_TYPE);
}

CA_FUNCTION(_empty_evaluate) {}

void function_with_hidden_state_term()
{
    Branch branch;
    Term* myfunc = import_function(branch, _empty_evaluate, "myfunc(state int)");
    Term* call_1 = branch.eval("myfunc()");
    Term* call_1_state = get_hidden_state_for_call(call_1);

    test_assert(branch[0] == myfunc);
    test_assert(branch[1] == call_1_state);
    test_assert(branch[2] == call_1);
    test_assert(is_stateful(call_1_state));
    test_assert(!is_stateful(call_1));

    Term* call_2 = branch.eval("myfunc()");
    Term* call_2_state = get_hidden_state_for_call(call_2);

    test_assert(is_stateful(call_2_state));
    test_assert(!is_stateful(call_2));
    test_assert(call_1_state != call_2_state);
}

void subroutine_expansion_during_migrate()
{
    Branch branch;

    branch.eval("def myfunc(); state int i; end");

    Branch& source = create_branch(branch, "source");
    Branch& dest = create_branch(branch, "dest");

    Term* sourceCall = source.eval("myfunc()");
    Term* destCall = dest.compile("myfunc()");

    Term* sourceCallState = get_hidden_state_for_call(sourceCall);
    Term* destCallState = get_hidden_state_for_call(destCall);

    test_assert(is_subroutine_state_expanded(sourceCallState));
    test_assert(!is_subroutine_state_expanded(destCallState));

    set_int(as_branch(sourceCallState)[0], 111);

    migrate_stateful_values(source, dest);

    //test_assert(is_subroutine_state_expanded(get_hidden_state_for_call(destCall)));
    test_assert(as_branch(destCallState)[0]->asInt() == 111);
}

void test_load_and_save()
{
    Branch branch;
    Term* statefulTerm = branch.eval("state int i");
    set_int(statefulTerm, 1);

    Branch state;
    Term* value_i = create_value(state, INT_TYPE, "i");
    set_int(value_i, 5);

    test_assert(as_int(statefulTerm) == 1);

    load_state_into_branch(state, branch);

    test_assert(as_int(statefulTerm) == 5);

    set_int(statefulTerm, 11);

    persist_state_from_branch(branch, state);

    test_assert(as_int(value_i) == 11);
}

void test_get_type_from_branches_stateful_terms()
{
    Branch branch;
    branch.eval("a = 0");
    branch.eval("state number b");
    branch.eval("c = 'hello'");
    branch.eval("state bool d");

    Branch type;
    
    get_type_from_branches_stateful_terms(branch, type);

    test_assert(type.length() == 2);
    test_assert(is_value(type[0]));
    test_assert(type[0]->type == FLOAT_TYPE);
    test_assert(is_value(type[0]));
    test_assert(type[1]->type == BOOL_TYPE);
}

void stateful_value_evaluation()
{
    Branch branch;
    Term *i = branch.eval("state i = 2.0");

    branch.compile("i = i + 1.0");

    test_equals(as_float(i), 2.0);
    evaluate_branch(branch);
    test_equals(as_float(i), 3.0);
    evaluate_branch(branch);
    test_equals(as_float(i), 4.0);
}

void initialize_from_expression()
{
    Branch branch;
    branch.eval("a = 1 + 2");
    branch.eval("b = a * 2");
    Term *c = branch.eval("state c = b");

    test_equals(to_float(c), 6);
}

void one_time_assignment()
{
    Branch branch;
    Term* a = create_int(branch, 3, "a");
    Term* s = branch.compile("state s = a");

    // change value before evaluate_branch, to make sure it's not stored
    // at compile time.
    set_int(a, 5);
    evaluate_branch(branch);
    test_assert(s);
    test_assert(as_int(s) == 5);

    // now make sure a subsequent evaluation doesn't change 's'
    set_int(a, 7);
    evaluate_branch(branch);
    test_assert(s);
    test_assert(as_int(s) == 5);
    set_int(a, 9);
    evaluate_branch(branch);
    test_assert(s);
    test_assert(as_int(s) == 5);
}

int NEXT_UNIQUE_OUTPUT = 0;

CA_FUNCTION(_unique_output)
{
    set_int(OUTPUT, NEXT_UNIQUE_OUTPUT++);
}

std::vector<int> SPY_RESULTS;

CA_FUNCTION(_spy)
{
    SPY_RESULTS.push_back(as_int(INPUT(0)));
}

void one_time_assignment_inside_for_loop()
{
    Branch branch;

    import_function(branch, _unique_output, "unique_output() -> int");
    import_function(branch, _spy, "spy(int)");
    branch.compile("for i in [1 1 1]\nstate s = unique_output()\nspy(s)\nend");

    NEXT_UNIQUE_OUTPUT = 0;
    SPY_RESULTS.clear();

    evaluate_branch(branch);

    test_assert(SPY_RESULTS.size() == 3);
    test_assert(SPY_RESULTS[0] == 0);
    test_assert(SPY_RESULTS[1] == 1);
    test_assert(SPY_RESULTS[2] == 2);

    SPY_RESULTS.clear();
    evaluate_branch(branch);

    test_assert(SPY_RESULTS.size() == 3);
    test_assert(SPY_RESULTS[0] == 0);
    test_assert(SPY_RESULTS[1] == 1);
    test_assert(SPY_RESULTS[2] == 2);
}

void state_inside_lots_of_nested_functions()
{
    Branch branch;

    import_function(branch, _unique_output, "unique_output() -> int");
    import_function(branch, _spy, "spy(int)");

    Term* f1 = branch.compile("def func1()\nstate s = unique_output()\nspy(s)\nend");
    Term* f2 = branch.compile("def func2()\nfunc1()\nend");
    Term* f3 = branch.compile("def func3()\nfunc2()\nend");
    Term* f4 = branch.compile("def func4()\nfunc3()\nend");

    test_assert(is_function_stateful(f1));
    test_assert(is_function_stateful(f2));
    test_assert(is_function_stateful(f3));
    test_assert(is_function_stateful(f4));

    NEXT_UNIQUE_OUTPUT = 11;
    SPY_RESULTS.clear();

    Term* call = branch.compile("func4()");
    test_assert(call->numInputs() == 1);
    evaluate_branch(branch);

    test_assert(SPY_RESULTS.size() == 1);
    test_assert(SPY_RESULTS[0] == 11);

    SPY_RESULTS.clear();

    evaluate_branch(branch);

    test_assert(SPY_RESULTS.size() == 1);
    test_assert(SPY_RESULTS[0] == 11);
}

void more_nested_state()
{
    Branch branch;

    import_function(branch, _unique_output, "unique_output() -> int");

    NEXT_UNIQUE_OUTPUT = 1;
    branch.eval("def f() state i = unique_output() end");
    branch.eval("def f2() f() end");

    branch.eval("a = f()");
    branch.eval("b = f2()");
    branch.eval("c = f2()");

    test_assert(branch.eval("inspect:get_state(a) == [1 true]"));
    test_assert(branch.eval("inspect:get_state(b) == [[2 true]]"));
    test_assert(branch.eval("inspect:get_state(c) == [[3 true]]"));
}

void migrate_subroutine_with_no_hidden_state()
{
    Branch source;
    source.eval("def hello()\nend");
    source.eval("hello()");

    Branch dest;
    dest.eval("def hello()\nend");
    dest.eval("hello()");

    migrate_stateful_values(source, dest);

    // Nothing to test, except to make sure that the above call didn't SIGABRT
    // (which it once did)
}

void test_migrate_stateful_compound_value()
{
    Branch source;
    Term* l_source = source.eval("state l = []");

    make_int(List::checkCast(l_source)->append(), 1);
    make_int(List::checkCast(l_source)->append(), 2);
    make_int(List::checkCast(l_source)->append(), 3);

    Branch dest;
    Term* l_dest = dest.eval("state l = []");

    test_assert(terms_match_for_migration(l_source, l_dest));

    migrate_stateful_values(source, dest);

    List* l_dest_list = List::checkCast(l_dest);
    test_assert(l_dest_list->numElements() == 3);
    test_assert(l_dest_list->getIndex(0)->asInt() == 1);
    test_assert(l_dest_list->getIndex(1)->asInt() == 2);
    test_assert(l_dest_list->getIndex(2)->asInt() == 3);

}

void test_reset_state()
{
    Branch branch;

    Term* i = branch.eval("state i = 5");

    test_assert(i->asInt() == 5);

    set_int(i, 11);

    test_assert(i->asInt() == 11);

    reset_state(branch);

    evaluate_branch(branch);

    test_assert(i->asInt() == 5);
}

void bug_where_stateful_function_wouldnt_update_inputs()
{
    Branch branch;

    branch.eval("def a() state i end");
    branch.eval("def b(int i) -> int; a(); return i; end");

    test_assert(branch);

    Term* x = branch.eval("x = 1");
    Term* b_call = branch.eval("b(x)");

    test_assert(b_call->asInt() == 1);

    set_int(x, 2);
    evaluate_branch(branch);

    test_assert(b_call->asInt() == 2);
}

void bug_where_state_wasnt_preserved_after_error()
{
    Branch branch;
    branch.eval("def hi() state int i; i = 4; ca_assert(false) end");

    Term* t = branch.eval("t = hi()");

    test_assert(get_hidden_state_for_call(t) != NULL);

    // not working because ca_assert() prevents us from reaching the part where the
    // stateful value is assigned back.
    //test_assert(get_hidden_state_for_call(t)->asBranch()[0]->asInt() == 4);
}

void test_load_state_into_branch()
{
    Branch branch;

    Term* f = branch.eval("def f(int i) state s = i end");
    branch.eval("def f2(int i) f(i) end");

    // Dirty up f() with leftover state
    branch.eval("f(5)");

    Branch& f_contents = f->nestedContents;
    test_assert(f_contents["s"]->asInt() == 5);

    Branch myState;
    load_state_into_branch(myState, f_contents);
    test_assert(f_contents["s"]->asInt() == 0);
}

void test_terms_match_for_migration()
{
    Branch branch;
    branch.eval("def f1() state int i end");
    branch.eval("def f2() state int i end");
    branch.eval("def f3() state number i end");

    Term* call1 = branch.eval("f1()");
    Term* call2 = branch.eval("f2()");

    Term* state1 = get_hidden_state_for_call(call1);
    Term* state2 = get_hidden_state_for_call(call2);

    test_assert(is_stateful(state1));
    test_assert(is_stateful(state2));

    test_assert(!terms_match_for_migration(state1, state2));
}

void test_changing_stateful_value_externally()
{
    Branch branch;
    branch.compile("state v = 'value'");

    set_str(branch["v"], "new");
    mark_stateful_value_assigned(branch["v"]);

    evaluate_branch(branch);

    test_equals(as_string(branch["v"]), "new");
}

void register_tests()
{
    REGISTER_TEST_CASE(stateful_code_tests::test_get_hidden_state_for_call);
    REGISTER_TEST_CASE(stateful_code_tests::test_simple);
    REGISTER_TEST_CASE(stateful_code_tests::function_with_hidden_state_term);
    REGISTER_TEST_CASE(stateful_code_tests::subroutine_expansion_during_migrate);
    REGISTER_TEST_CASE(stateful_code_tests::test_load_and_save);
    REGISTER_TEST_CASE(stateful_code_tests::test_get_type_from_branches_stateful_terms);
    REGISTER_TEST_CASE(stateful_code_tests::stateful_value_evaluation);
    REGISTER_TEST_CASE(stateful_code_tests::initialize_from_expression);
    REGISTER_TEST_CASE(stateful_code_tests::one_time_assignment);
    REGISTER_TEST_CASE(stateful_code_tests::one_time_assignment_inside_for_loop);
    REGISTER_TEST_CASE(stateful_code_tests::state_inside_lots_of_nested_functions);
    REGISTER_TEST_CASE(stateful_code_tests::more_nested_state);
    REGISTER_TEST_CASE(stateful_code_tests::migrate_subroutine_with_no_hidden_state);
    REGISTER_TEST_CASE(stateful_code_tests::test_migrate_stateful_compound_value);
    REGISTER_TEST_CASE(stateful_code_tests::test_reset_state);
    REGISTER_TEST_CASE(stateful_code_tests::bug_where_stateful_function_wouldnt_update_inputs);
    REGISTER_TEST_CASE(stateful_code_tests::bug_where_state_wasnt_preserved_after_error);
    REGISTER_TEST_CASE(stateful_code_tests::test_load_state_into_branch);
    REGISTER_TEST_CASE(stateful_code_tests::test_terms_match_for_migration);
    REGISTER_TEST_CASE(stateful_code_tests::test_changing_stateful_value_externally);
}

} // namespace stateful_code_tests

} // namespace circa
