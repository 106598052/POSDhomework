#include "atom.h"
#include "number.h"
#include "variable.h"

bool Atom :: match(Number *number){
   return MATCH_ATOM_TO_NUMBER_FAILURE;
}
bool Atom ::match(Number& number){
  return MATCH_ATOM_TO_NUMBER_FAILURE;
}
bool Atom:: operator ==(Atom a){
  return _symbol == a._symbol;
}

bool Atom:: match(Variable *X){
  bool return_value = false;
  if(X->_assignable){
    X->setvalue(_symbol);
    X->setassignable();
    return_value = true;
  }
  else{
    return_value = (_symbol == X->value());
  }
  return return_value;
}
bool Atom:: match(Variable& X){
  bool return_value = false;
  if(X._assignable){
    X.setvalue(_symbol);
    X.setassignable();
    return_value = true;
  }
  else{
    return_value = (_symbol == X.value());
  }
  return return_value;
}
