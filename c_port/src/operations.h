
#include "function.h"
#include "term.h"
#include "type.h"

namespace circa {

Term* create_term(Branch* branch, Term* function, TermList inputs);
void initialize_term(Term* term, Term* function, TermList inputs);
void set_inputs(Term* term, TermList inputs);
Term* create_constant(Branch* branch, Term* type);
void change_type(Term* term, Term* type);
void specialize_type(Term* term, Term* type);
void set_input(Term* term, int index, Term* input);
void execute(Term* term);
void execute_branch(Branch* branch);

// Examine 'function' and 'inputs' and returns a result term. A few things
// may happen here:
//  1. We might re-use an existing term
//  2. 'function' might be a type (create an empty instance)
//  3. We might specialize an overloaded function
//  4. add more stuff here
Term* apply_function(Branch* branch, Term* function, TermList inputs);

// Perform 'apply_function' and then execute the result
Term* exec_function(Branch* branch, Term* function, TermList inputs);

// Fetch the const function for this type
Term* get_const_function(Branch* branch, Term* type);

void change_function(Term* term, Term* new_function);
void copy_value(Term* source, Term* dest);
void steal_value(Term* source, Term* dest);

void duplicate_branch(Term* source, Term* dest);

Term* find_named(Branch* branch, std::string name);

Term* constant_string(Branch* branch, std::string s);
Term* constant_int(Branch* branch, int i);
Term* constant_list(Branch* branch, TermList list);

} // namespace circa
