#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>
#include "atom.h"
#include <vector>

using std::string;

class Atom;
class Number;
class Struct;
class Variable:public Term{
public:
  Variable(string s):_symbol(s),_value(s){}
  string _symbol;
  string _value;
  string symbol()const;
  string value()const;
  bool match(Atom& atom);
  bool match(Number& num);
  bool match(Variable& var);
  bool match(Struct& s);
  bool _assignable = true;
  void setvalue(string s);
  void setassignable();
  bool arg_has_match = false;
  bool match_struct_before = false;
  string var_match_struct = "";

private:
  std::vector<string *> _args = {&_value};
  //bool _assignable = true;
};

#endif
