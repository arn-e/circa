// Copyright (c) Paul Hodge. See LICENSE file for license terms.

#pragma once

#include "common_headers.h"
#include "type.h"

namespace circa {
namespace handle_t {

    typedef void (*OnRelease)(TValue* data);

    // Initialize the given handle with a value. The value is consumed by this call.
    void set(TValue* handle, Type* type, TValue* value /* consumed */);

    // Convenience function to initalize a handle with an opaque pointer value.
    void set(TValue* handle, Type* type, void* opaquePointer);

    TValue* get(TValue* value);
    void* get_ptr(TValue* value);
    int refcount(TValue* value);
    void setup_type(Type* type);

    template <typename T>
    T* create(TValue* value, Type* type)
    {
        T* obj = new T();
        set(value, type, obj);
        return obj;
    }

    template <typename T>
    void templated_release_func(TValue* value)
    {
        T* object = (T*) as_opaque_pointer(value);
        delete object;
    }

    template <typename T>
    void setup_type(Type* type)
    {
        setup_type(type);
        OnRelease callback = templated_release_func<T>;
        set_opaque_pointer(&type->parameter, (void*) callback);
    }

} // namespace handle_t

template <typename T>
Type* setup_type_as_handle(Branch* branch, const char* name)
{
    Type* type = get_declared_type(branch, name);
    handle_t::setup_type<T>(type);
    return type;
}

template <typename T>
class HandleWrapper {
public:
    Type* type;

    HandleWrapper() : type(NULL) {}

    void initialize(Branch* branch, const char* name)
    {
        type = get_declared_type(branch, name);

        if (type == NULL)
            internal_error("HandleWrapper::initialize couldn't find type");

        handle_t::setup_type<T>(type);
    }
    void set(TValue* tv, T* value)
    {
        ca_assert(type != NULL);
        handle_t::set(tv, type, value);
    }
    T* get(TValue* tv)
    {
        return (T*) handle_t::get_ptr(tv);
    }
};

} // namespace circa
