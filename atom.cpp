#include "atom.h"
#include "number.h"
#include "variable.h"

bool Atom ::match(Variable& var){
  if(var.isvar){
    var._value = _symbol;
    return true;
  }
  else{
    return symbol() == var.symbol();
  }
}

bool Atom ::match(Atom & tom) {
  return symbol() == tom.symbol();
}
