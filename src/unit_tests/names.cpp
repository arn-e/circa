// Copyright (c) Andrew Fischer. See LICENSE file for license terms.

#include "unit_test_common.h"

#include "building.h"
#include "code_iterators.h"
#include "evaluation.h"
#include "fakefs.h"
#include "inspection.h"
#include "kernel.h"
#include "modules.h"
#include "names.h"
#include "string_type.h"

namespace names {

void find_name()
{
    Branch branch;
    branch.compile("a = 1");
    branch.compile("namespace ns { a = 2; b = 3; } ");

    test_equals(term_value(find_name(&branch, "a")), "1");
    test_equals(term_value(find_name(&branch, "ns:a")), "2");
    test_equals(term_value(find_name(&branch, "ns:b")), "3");
}

void unique_ordinals()
{
    Branch branch;
    Term* a = branch.compile("a = 1");
    Term* b = branch.compile("b = 1");

    test_equals(a->uniqueOrdinal, 0);
    test_equals(b->uniqueOrdinal, 0);

    Term* a2 = branch.compile("a = 3");
    test_equals(a->uniqueOrdinal, 1);
    test_equals(a2->uniqueOrdinal, 2);

    Term* a3 = branch.compile("a = 3");
    test_equals(a3->uniqueOrdinal, 3);

    Term* x = branch.compile("x = 4");
    test_equals(x->uniqueOrdinal, 0);
    rename(x, name_from_string("a"));
    test_equals(x->uniqueOrdinal, 4);
}

void global_names()
{
    Branch* branch = find_or_create_branch(global_root_branch(), "names_test");

    Term* a = branch->compile("a = 1");

    circa::Value globalName;
    get_global_name(a, &globalName);
    test_equals(&globalName, "names_test:a");

    Term* a_2 = branch->compile("a = 2");
    get_global_name(a, &globalName);
    test_equals(&globalName, "names_test:a#1");

    get_global_name(a_2, &globalName);
    test_equals(&globalName, "names_test:a#2");

    Branch* branch2 = create_branch(branch, "branch2");
    Term* b = branch2->compile("b = 3");
    Term* b_2 = branch2->compile("b = 4");

    get_global_name(b, &globalName);
    test_equals(&globalName, "names_test:branch2:b#1");
    get_global_name(b_2, &globalName);
    test_equals(&globalName, "names_test:branch2:b#2");

    // Now try finding terms via their global name.
    test_assert(find_from_global_name(global_world(), "names_test:a") == a_2);
    test_assert(find_from_global_name(global_world(), "names_test:a#1") == a);
    test_assert(find_from_global_name(global_world(), "names_test:a#2") == a_2);
    test_assert(find_from_global_name(global_world(), "names_test:branch2:b") == b_2);
    test_assert(find_from_global_name(global_world(), "names_test:branch2:b#1") == b);
    test_assert(find_from_global_name(global_world(), "names_test:branch2:b#2") == b_2);
}

void test_find_ordinal_suffix()
{
    int endPos;

    endPos = 1;
    test_equals(name_find_ordinal_suffix("a", &endPos), -1);
    test_equals(endPos, 1);

    endPos = 3;
    test_equals(name_find_ordinal_suffix("a#2", &endPos), 2);
    test_equals(endPos, 1);

    endPos = 3;
    test_equals(name_find_ordinal_suffix("a##", &endPos), -1);
    test_equals(endPos, 3);

    endPos = 3;
    test_equals(name_find_ordinal_suffix("a12", &endPos), -1);
    test_equals(endPos, 3);

    endPos = 3;
    test_equals(name_find_ordinal_suffix("#12", &endPos), 12);
    test_equals(endPos, 0);

    endPos = 7;
    test_equals(name_find_ordinal_suffix("a#2:b#3", &endPos), 3);
    test_equals(endPos, 5);

    endPos = 3;
    test_equals(name_find_ordinal_suffix("a#2:b#3", &endPos), 2);
    test_equals(endPos, 1);
    
    // test using -1 as the end position
    endPos = -1;
    test_equals(name_find_ordinal_suffix("a#2", &endPos), 2);
    test_equals(endPos, 1);
}

void search_every_global_name()
{
    // This test is brave. We go through every single term in the world, find its
    // global name (if it exists), then see if we can find the original term using
    // the global name.

    circa::Value globalName;
    for (BranchIterator it(global_root_branch()); it.unfinished(); it.advance()) {
        get_global_name(*it, &globalName);

        if (!is_string(&globalName))
            continue;

        Term* searchResult = find_from_global_name(global_world(), as_cstring(&globalName));

        if (searchResult != *it) {
            std::cout << "Global name search failed for term: " << global_id(*it)
                << ", with global name: " << as_cstring(&globalName) << std::endl;
            declare_current_test_failed();
        }
    }
}

void bug_with_lookup_type_and_qualified_name()
{
    // Bug repro. There was an issue where, when searching for a qualified name, we would
    // use the original lookup type on the prefix. (which is wrong).

    Branch branch;
    Branch* module = create_branch(&branch, "module");
    Term* T = create_type(module, "T");

    test_assert(T == find_name(&branch, "module:T", -1, name_LookupType));
}

void type_name_visible_from_module()
{
    FakeFilesystem fs;
    fs.set("a", "type A { int i }");
    fs.set("b", "require a\ntest_spy(make(A))");

    load_module_file(global_world(), "a", "a");
    Branch* b = load_module_file(global_world(), "b", "b");

    Stack stack;
    push_frame(&stack, b);
    test_spy_clear();
    run_interpreter(&stack);

    test_equals(test_spy_get_results(), "[[0]]");
}

void register_tests()
{
    REGISTER_TEST_CASE(names::find_name);
    REGISTER_TEST_CASE(names::global_names);
    REGISTER_TEST_CASE(names::unique_ordinals);
    REGISTER_TEST_CASE(names::test_find_ordinal_suffix);
    REGISTER_TEST_CASE(names::search_every_global_name);
    REGISTER_TEST_CASE(names::bug_with_lookup_type_and_qualified_name);
    REGISTER_TEST_CASE(names::type_name_visible_from_module);
}

} // namespace names
