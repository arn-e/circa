// Copyright (c) Paul Hodge. See LICENSE file for license terms.

#pragma once

namespace circa {

namespace subroutine_f {
    void format_source(StyledSource* source, Term* term);
}

CA_FUNCTION(evaluate_subroutine);

bool is_subroutine(Term* term);
Term* find_enclosing_subroutine(Term* term);
int get_input_index_of_placeholder(Term* inputPlaceholder);

// Perform various steps to finish creating a subroutine
Term* create_subroutine(Branch* branch, const char* name);
void initialize_subroutine(Term* sub);
void finish_building_subroutine(Term* sub, Term* outputType);

void store_locals(Branch* branch, TValue* storage);
void restore_locals(TValue* storageTv, Branch* branch);

void call_subroutine(Branch* sub, TValue* inputs, TValue* output, TValue* error);
void call_subroutine(Term* sub, TValue* inputs, TValue* output, TValue* error);


} // namespace circa
