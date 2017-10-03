#include "variable.h"
#include "number.h"
#include "atom.h"

string Variable ::value(){
  return _value;
}
bool Variable ::match(Atom *atom){
  bool return_value = _assignable;
  if(_assignable){
    _value = atom->_symbol;
    _assignable = false;
  }
  else{
    return_value = (_value == atom->_symbol);
  }
  return return_value;
}
bool Variable ::match(Number *num){
  bool return_value = _assignable;
  if(_assignable){
    _value = num->value();
    _assignable = false;
  }
  else{
    return_value = (_value == num->value());
  }
  return return_value;
}
void Variable ::setvalue(string s){
  _value = s ;
}
void Variable ::setassignable() {
  _assignable = false ;
}
