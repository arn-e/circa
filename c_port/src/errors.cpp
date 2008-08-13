
#include "common_headers.h"

#include "errors.h"
#include "term.h"
#include "type.h"

namespace circa {

namespace errors {

string
TypeError::message()
{
    // The goal here is to assume as little as possible

    if (!is_type(expectedType))
        throw InternalError("2nd argument to TypeError must be a type");
    std::string expected = as_type(expectedType)->name;

    if (offendingTerm == NULL)
        return std::string("Term is NULL (expected ") + expected + ")";

    if (offendingTerm->type == NULL)
        return std::string("Term '") + offendingTerm->findName() + "' has NULL type "
            "(expected " + expected + ")";

    if (!is_type(offendingTerm->type))
        return std::string("The type field of '") + offendingTerm->findName()
            + "' is not a type. (expected " + expected + ")";

    return string("TypeError: expected " + as_type(expectedType)->name
            + ", found " + as_type(offendingTerm->type)->name + " \""
            + offendingTerm->findName()) + "\"";
}

} // namespace errors
} // namespace circa
