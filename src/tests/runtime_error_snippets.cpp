// Copyright (c) 2007-2009 Andrew Fischer. All rights reserved.

#include <circa.h>

namespace circa {
namespace runtime_error_snippets {

void test_input(std::string const& in)
{
    Branch branch;
    parser::compile(&branch, parser::statement_list, in);

    if (has_static_errors(branch)) {
        std::cout << "In code snippet: " << in << std::endl;
        print_static_errors_formatted(branch, std::cout);
        dump_branch(branch);
        declare_current_test_failed();
        return;
    }

    Term errorListener;
    evaluate_branch(branch, &errorListener);

    if (!errorListener.hasError()) {
        std::cout << "No runtime error: " << in << std::endl;
        dump_branch(branch);
        declare_current_test_failed();
        return;
    }
    
    std::stringstream formattedError;
    print_runtime_error_formatted(branch, formattedError);

    if (formattedError.str().find("!!! no error found") != std::string::npos) {
        std::cout << formattedError.str();
        declare_current_test_failed();
    }
}

void test_runtime_errors()
{
    test_input("assert(false)");
    test_input("if true assert(false) end");
    test_input("for i in [1] assert(false) end");
    test_input("def hey() assert(false) end; hey()");
    test_input("def hey()::bool assert(false) return true end; if hey() end");
}

void register_tests()
{
    REGISTER_TEST_CASE(runtime_error_snippets::test_runtime_errors);
}

} // namespace runtime_tests

} // namespace circa