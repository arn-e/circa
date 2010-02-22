// Copyright (c) 2007-2010 Paul Hodge. All rights reserved.

#include "circa.h"

namespace circa {

Term* ANY_TYPE = NULL;
Term* BOOL_TYPE = NULL;
Term* FLOAT_TYPE = NULL;
Term* INT_TYPE = NULL;
Term* REF_TYPE = NULL;
Term* STRING_TYPE = NULL;

// thunks for Function:
Term* EVALUATE_THUNK_TYPE = NULL;
Term* SPECIALIZE_THUNK_TYPE = NULL;

// common thunks:
Term* TO_STRING_THUNK_TYPE = NULL;
Term* CHECK_INVARIANTS_THUNK_TYPE = NULL;

EvaluateFunc& as_evaluate_thunk(Term* term)
{
    assert_type(term, EVALUATE_THUNK_TYPE);
    return ((EvaluateFunc&) term->value_data.ptr);
}

SpecializeTypeFunc& as_specialize_type_thunk(Term* term)
{
    assert_type(term, SPECIALIZE_THUNK_TYPE);
    return ((SpecializeTypeFunc&) term->value_data.ptr);
}

ToSourceStringFunc& as_to_source_string_thunk(Term* term)
{
    assert_type(term, TO_STRING_THUNK_TYPE);
    return ((ToSourceStringFunc&) term->value_data.ptr);
}

CheckInvariantsFunc& as_check_invariants_thunk(Term* term)
{
    assert_type(term, CHECK_INVARIANTS_THUNK_TYPE);
    return ((CheckInvariantsFunc&) term->value_data.ptr);
}

namespace any_t {
    std::string to_string(Term* term)
    {
        return "<any>";
    }
}

namespace void_t {
    std::string to_string(Term*)
    {
        return "<void>";
    }
}

void initialize_primitive_types(Branch& kernel)
{
    EVALUATE_THUNK_TYPE = import_pointer_type<EvaluateFunc>(kernel, "EvaluateThunk");
    SPECIALIZE_THUNK_TYPE = import_pointer_type<SpecializeTypeFunc>(kernel, "SpecializeThunk");
    TO_STRING_THUNK_TYPE = import_pointer_type<ToSourceStringFunc>(kernel, "ToSourceStringThunk");
    CHECK_INVARIANTS_THUNK_TYPE = import_pointer_type<CheckInvariantsFunc>(kernel, "CheckInvariantsThunk");

    STRING_TYPE = create_type(kernel, "string");
    set_pointer(STRING_TYPE, STRING_T);

    INT_TYPE = create_type(kernel, "int");
    set_pointer(INT_TYPE, INT_T);

    FLOAT_TYPE = create_type(kernel, "number");
    set_pointer(FLOAT_TYPE, FLOAT_T);

    BOOL_TYPE = create_type(kernel, "bool");
    set_pointer(BOOL_TYPE, BOOL_T);

    REF_TYPE = create_type(kernel, "Ref");
    set_pointer(REF_TYPE, REF_T);

    // ANY_TYPE was created in bootstrap_kernel
    Type* anyType = &as_type(ANY_TYPE);
    anyType->toString = any_t::to_string;

    VOID_TYPE = create_empty_type(kernel, "void");
    Type* voidType = &as_type(VOID_TYPE);
    voidType->toString = void_t::to_string;
}

void post_setup_primitive_types()
{
    import_member_function(STRING_TYPE, string_t::length, "length(string) -> int");
    import_member_function(STRING_TYPE, string_t::substr, "substr(string,int,int) -> string");

    import_member_function(REF_TYPE, ref_t::get_name, "name(Ref) -> string");
    import_member_function(REF_TYPE, ref_t::hosted_to_string, "to_string(Ref) -> string");
    import_member_function(REF_TYPE, ref_t::hosted_typeof, "typeof(Ref) -> Ref");
    import_member_function(REF_TYPE, ref_t::get_function, "function(Ref) -> Ref");
    import_member_function(REF_TYPE, ref_t::assign, "assign(Ref, any)");
    import_member_function(REF_TYPE, ref_t::tweak, "tweak(Ref, int steps)");
    import_member_function(REF_TYPE, ref_t::asint, "asint(Ref) -> int");
    import_member_function(REF_TYPE, ref_t::asfloat, "asfloat(Ref) -> number");
    import_member_function(REF_TYPE, ref_t::get_input, "input(Ref, int) -> Ref");
    import_member_function(REF_TYPE, ref_t::num_inputs, "num_inputs(Ref) -> int");
    import_member_function(REF_TYPE, ref_t::get_source_location,
            "source_location(Ref) -> Point_i");
}

} // namespace circa
