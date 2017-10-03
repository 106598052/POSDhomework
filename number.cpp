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
  x->setvalue(value());
  number_variable_match = true;
  return number_variable_match;
}
