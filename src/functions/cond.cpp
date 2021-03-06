// Copyright (c) Andrew Fischer. See LICENSE file for license terms.

#include "circa/internal/for_hosted_funcs.h"

namespace circa {
namespace cond_function {

    void cond_evaluate(caStack* stack)
    {
        int index = circa_bool_input(stack, 0) ? 1 : 2;
        copy(circa_input(stack, index), circa_output(stack, 0));
    }

    Type* specializeType(Term* caller)
    {
        List choices;
        set_type_list(&choices, caller->input(1)->type, caller->input(2)->type);
        return find_common_type(&choices);
    }

    CA_FUNCTION(feedback)
    {
#if 0
OLD_FEEDBACK_IMPL_DISABLED
        Term* target = INPUT_TERM(0);
        Term* desired = INPUT_TERM(1);
        Block* output = feedback_output(CALLER);

        // cond(condition, pos, neg)
        //
        // For condition, don't try to send feedback
        copy(target->input(0), output[0]);

        // For pos and neg, pass along the feedback that we have received,
        // depending on the value of cond
        bool cond = target->input(0)->asBool();

        int indexUsed = cond ? 1 : 2;

        for (int i=1; i <= 2; i++) {
            Term* signal = (i == indexUsed) ? desired : target->input(i);
            copy(signal, output[i]);
        }
        #endif
    }

    void setup(Block* kernel)
    {
        FUNCS.cond = import_function(kernel, cond_evaluate,
                "cond(bool condition, any pos, any neg) -> any"
                "-- If 'condition' is true, returns 'pos'. Otherwise returns 'neg'.");
        function_set_specialize_type_func(FUNCS.cond, specializeType);
    }
}
}
