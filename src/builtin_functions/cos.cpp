// Copyright 2008 Andrew Fischer

#include "circa.h"

namespace circa {
namespace cos_function {

    void evaluate(Term* caller)
    {
        float input = to_float(caller->input(0));
        // Convert input from 0..1 to 0..2pi
        as_float(caller) = cos(float(input * 2 * M_PI));
    }

    void feedback_evaluate(Term* caller)
    {
        // Term* target = caller->input(0);
        float desired = caller->input(1)->toFloat();

        // restrict input to -1..1
        if (desired > 1)
            desired = std::fmod(desired + 1, 2.0f) - 1;

        // TODO: find a value that is in the same period as the target's input

        float result = std::acos(desired);

        // Map result from radians into range of 0..1
        as_float(caller) = result / float(2 * M_PI);
    }

    void setup(Branch& kernel)
    {
        Term* func = import_function(kernel, evaluate, "cos(float) : float");
        function_t::get_feedback_func(func) = 
            import_function(kernel, feedback_evaluate, "cos_feedback(any, float) : float");
    }
}
}
