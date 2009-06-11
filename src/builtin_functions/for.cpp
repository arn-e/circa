// Copyright 2008 Paul Hodge

#include <circa.h>

namespace circa {
namespace for_function {

    void evaluate(Term* caller)
    {
        evaluate_for_loop(caller, caller->input(0));
    }

    std::string toSourceString(Term* term)
    {
        std::stringstream result;
        result << "for ";
        result << get_for_loop_iterator(term)->name;
        result << " in ";
        result << get_source_of_input(term,0);
        result << "\n";
        result << get_branch_source(get_for_loop_code(term));
        result << "end";

        return result.str();
    }

    void setup(Branch& kernel)
    {
        create_type(&kernel, "type for__state { Branch code, List _state }");
        FOR_FUNC = import_function(kernel, evaluate, "for(List) : for__state");
        as_function(FOR_FUNC).toSourceString = toSourceString;
    }
}
} // namespace circa
