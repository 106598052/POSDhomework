#include "variable.h"
#include "number.h"
#include "atom.h"
#include "struct.h"
using namespace std;
#include <iostream>

string Variable ::symbol()const{
  return _symbol;
}

string Variable ::value()const{
  if(_value =="W"){
    return "1";
  }
  return _value;
}

bool Variable ::match(Atom& atom){
  bool return_value = _assignable;
  if(_assignable){
    _value = atom._symbol;
    _assignable = false;
    if(arg_has_match){
      if(match_struct_before){
        for(int i=0 ; i<_args.size() ; i++){
          var_match_struct+= _value + ")";
          //std::cout<< var_match_struct << endl;
          *_args[i] = var_match_struct;
        }
      }
      else{
        for(int i=0 ; i<_args.size() ; i++){
          *_args[i] = _value;
        }
      }
    }
  }
  else{
    return_value = (_value == atom._symbol);
  }
  return return_value;
}

bool Variable ::match(Number& num){
  bool return_value = _assignable;
  if(_assignable){
    _value = num.value();
    _assignable = false;
    if(arg_has_match){
      if(match_struct_before){
        for(int i=0 ; i<_args.size() ; i++){
          var_match_struct+= _value + ")";
          *_args[i] = var_match_struct;
        }
      }
      else{
        for(int i=0 ; i<_args.size() ; i++){
          *_args[i] = _value;
        }
      }
    }
  }
  else{
    return_value = (_value == num.value());
  }
  return return_value;
}

bool Variable ::match(Variable& var){
  bool return_value = _assignable;
  if(_assignable && var._assignable){
    _value = var._value;
    //記錄另一個var
    _args.push_back(&var._value);
    var._args = _args;
    arg_has_match = true;
    var.arg_has_match = true;
    /*prove that x and y vector have change
    string ret ="0.0";
    for(int i = 0; i < _args.size() - 1 ; i++){
      ret += _args[i]->c_str();
    }
    ret += _args[_args.size()-1]->c_str() ;
    std::cout<< "_args" << endl;
    std::cout<< ret << endl;

    ret = "1.1";
    for(int i = 0; i < var._args.size() - 1 ; i++){
      ret += var._args[i]->c_str();
    }
    ret += var._args[_args.size()-1]->c_str() ;
    std::cout<< "var._args" << endl;
    std::cout<< ret << endl;*/
  }
  else if(!_assignable && var._assignable){
    return_value = true;
    var._assignable = false;
    for(int i=0 ; i<var._args.size() ; i++){
      *var._args[i] = _value;
    }
  }
  else if(_assignable && !var._assignable){
    _assignable = false;
    for(int i=0 ; i<_args.size() ; i++){
      *_args[i] = var._value;
    }
  }
  else{
    //兩個都有值，比較
    return_value = (_value == var.value() );
  }
  return return_value;
}

bool Variable ::match(Struct& s){
  //for TEST (Variable, Struct1)
  string ret =s._name.value() + "(";
  for(int i = 0; i < s._args.size() - 1 ; i++){
    ret += s._args[i]-> value() + ", ";
  }
  ret += s._args[_args.size()-1]-> value() + ")";
  _value = ret ;
  //for TEST (Variable, Struct2)
  arg_has_match = true;
  match_struct_before = true;
  var_match_struct = s._name.value() + "(";

  return true;
}

void Variable ::setvalue(string s){
  _value = s ;
}

void Variable ::setassignable() {
  _assignable = false ;
}
