#include "number.h"
#include <string>
#include "atom.h"
#include "variable.h"
using namespace std;
#include <iostream>
#include <sstream>

string Number ::symbol(){
  return to_string(_value);
}
string Number ::value(){
  std::ostringstream strs;
  strs << _value;
  std::string str = strs.str();
  return str;
}
bool Number ::match(Number& num){
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
bool Number ::match(Atom& atom){
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
  else{
    return_value = (value() == x->value());
  }
  return return_value;
}
bool Number ::match(Variable& x){
  bool return_value = x._assignable;
  if(x._assignable){
    x.setvalue(value());
    x._assignable = false;
  }
  else{
    return_value = (value() == x.value());
  }
  return return_value;
}
/*don't need
double Number ::check_number(double value){
  int point = 0;
  double b = value;
  double a = (int) b;
  double result = value - a;
  //std::cout<< result << endl;
  while(result!=0){
    b = b *10 ;
    a = (int) b;
    //std::cout<< a << endl;
    result = b - a;
    //std::cout<< result << endl;
    point++;
  }
  //std::cout<< point << endl;

  for(int i=0 ; i < point ;i++){
    b = b / 10 ;
  }
  std::cout<< "b: " << b << endl;
  return b ;
}*/
