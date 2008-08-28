
#include "common_headers.h"

#include "cpp_interface.h"
#include "branch.h"
#include "parser.h"
#include "tests/common.h"

class MyDumbType {
public:
    static int timesConstructorCalled;
    static int timesDestructorCalled;

    std::string hi;

    MyDumbType() {
        timesConstructorCalled++;
    }
    ~MyDumbType() {
        timesDestructorCalled++;
    }
};

int MyDumbType::timesConstructorCalled = 0;
int MyDumbType::timesDestructorCalled = 0;

namespace circa {
namespace cpp_interface_tests {

void test_simple() {
    Branch branch;

    MyDumbType::timesConstructorCalled = 0;
    quick_create_cpp_type<MyDumbType>(&branch, "MyDumbType");

    test_assert(MyDumbType::timesConstructorCalled == 0);
    Term* term = parser::quick_eval_statement(&branch, "a = MyDumbType()");
    test_assert(MyDumbType::timesConstructorCalled == 1);

}

} // namespace cpp_interface_tests

void register_cpp_interface_tests()
{
    REGISTER_TEST_CASE(cpp_interface_tests::test_simple);
}

} // namespace circa
