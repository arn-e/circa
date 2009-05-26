// Copyright 2009 Paul Hodge

#ifndef CIRCA_SUBROUTINE_INCLUDED
#define CIRCA_SUBROUTINE_INCLUDED

namespace circa {

namespace subroutine_t {
    std::string to_string(Term* term);
}

bool is_subroutine(Term* term);
Function& get_subroutines_function_def(Term* term);
void initialize_subroutine(Term* term);
Branch& call_subroutine(Branch& branch, std::string const& functionName);
void subroutine_call_evaluate(Term* caller);
Term* get_state_for_subroutine_call(Term* term);
bool is_subroutine_state_expanded(Term* term);
void expand_subroutines_hidden_state(Term* call, Term* state);

} // namespace circa

#endif // CIRCA_SUBROUTINE_INCLUDED
