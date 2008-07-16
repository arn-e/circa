
#include "function.h"

#define CA_FUNCTION(t) ((CircaFunction*)t->outputValue)

CircaObject* CaFunction_alloc(Term*)
{
    return new CircaFunction();
}

void CaFunction_setPureFunction(Term* term, bool value)
{
    CA_FUNCTION(term)->pureFunction = value;
}
void CaFunction_setName(Term* term, const char* value)
{
    CA_FUNCTION(term)->name = value;
}
void CaFunction_setInputType(Term* term, int index, Term* type)
{
    CA_FUNCTION(term)->inputTypes.setAt(index, type);
}
void CaFunction_setOutputType(Term* term, int index, Term* type)
{
    CA_FUNCTION(term)->outputTypes.setAt(index, type);
}
