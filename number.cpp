#include "number.h"
#include <string>
#include "atom.h"
#include "variable.h"

using namespace std;

string Number ::symbol(){
  return to_string(_value);
}
string Number ::value(){
  return to_string(_value);
}
bool Number ::match(Number num){
  if(to_string(_value) ==num.value()){
    number_match_or_not_match = true;
  }
  return number_match_or_not_match ;
}
bool Number ::match(Number *num){
  if(_value==num->_value){
    number_match_or_not_match = true;
  }
  return number_match_or_not_match ;
}
bool Number ::match(Atom atom){
  return number_atom_not_match;
}
bool Number ::match(Atom *atom){
  return number_atom_not_match;
}
bool Number ::match(Variable *x){
  bool return_value = x->_assignable;
  if(x->_assignable){
    x->setvalue(value());
    x->_assignable = false;
  }
  return return_value;
}
bool Number ::match(Variable x){
  bool return_value = x._assignable;
  if(x._assignable){
    x.setvalue(value());
    x._assignable = false;
  }
  return return_value;
}
