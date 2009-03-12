// Copyright 2009 Andrew Fischer

#include "common_headers.h"

#include "circa.h"

namespace circa {

void generate_training(Branch& branch, Term* subject, Term* delta)
{
    Function& targetsFunction = as_function(subject->function);

    if (targetsFunction.generateTraining != NULL)
    {
        targetsFunction.generateTraining(branch, subject, delta);
    } else {
        std::cout << "warn: function " << targetsFunction.name <<
            " doesn't have a generateTraining function" << std::endl;
        return;
    }
}

} // namespace circa
