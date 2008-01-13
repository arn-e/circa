
import builtin_functions
import ca_function
import builder
import term
import string

global_builder = builder.Builder()

def wrap(func):
  def wrapped_circa_func(*args):

    # if they use any non-term args, convert them to Circa terms
    args = list(args)
    for i in range(len(args)):
      arg = args[i]

      if not isinstance(arg, term.Term):
        args[i] = global_builder.createConstant(arg)

    new_term = global_builder.createTerm(func, inputs=args)
    new_term.evaluate()
    return new_term

  return wrapped_circa_func

__all__ = []

# go through builtin_functions, wrap anything that's a function,
# add it to this module
for name in dir(builtin_functions):
  obj = getattr(builtin_functions, name)
  name = string.lower(name)   # lower-case the name
  if isinstance(obj, ca_function.BaseFunction):
    print "wrapping " + name
    globals()[name] = wrap(obj)
    __all__.append(name)

# replace 'constant' and 'variable' functions with versions that makes sense
def constant(value):
  return global_builder.createConstant(value)
def variable(value):
  return global_builder.createVariable(value)

__all__ += [ 'constant' , 'variable' ]
