#include "term.h"
#include "variable.h"

bool Term::match(Term & a){
  if (typeid(a) ==  typeid(Variable))
    return a.match(*this); 
  else
    return symbol() == a.symbol();
}
