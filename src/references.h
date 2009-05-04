// Copyright 2008 Andrew Fischer

#ifndef CIRCA_REFERENCES_INCLUDED
#define CIRCA_REFERENCES_INCLUDED

#include "common_headers.h"

namespace circa {

struct Ref
{
    Term* _t;

    Ref()
      : _t(NULL)
    {}

    Ref(Term *initialValue) : _t(NULL)
    {
        set(initialValue);
    }

    // Copy constructor
    Ref(Ref const& copy) : _t(NULL)
    {
        set(copy._t);
    }

    ~Ref()
    {
        set(NULL);
    }

    // Assignment copy
    Ref& operator=(Ref const& rhs)
    {
        set(rhs._t);
        return *this;
    }

    void set(Term* target);

    Ref& operator=(Term* target)
    {
        set(target);
        return *this;
    }

    bool operator==(Term* t) const
    {
        return _t == t;
    }

    operator Term*() const
    {
        return _t;
    }

    operator Term*&()
    {
        return _t;
    }

    Term* operator->()
    {
        return _t;
    }

    static void remap_pointers(Term* term, ReferenceMap const& map);
    static ReferenceIterator* start_reference_iterator(Term* term);
};

void delete_term(Term* term);
void remap_pointers(Term* term, ReferenceMap const& map);
void remap_pointers(Term* term, Term* original, Term* replacement);
void remap_pointers(Branch& branch, Term* original, Term* replacement);

} // namespace circa

#endif // CIRCA_REFERENCE_INCLUDED
