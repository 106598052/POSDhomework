#include "variable.h"

string Variable::value() const {
  if (_inst)
    return _inst->value();
  else
    return Term::value();
}

bool Variable::match( Term & term ){
  if (this == &term)
    return true;
  if(!_inst){
    _inst = &term ;
    return true;
  }
  return _inst->match(term);
}
