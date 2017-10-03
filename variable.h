#ifndef VARIABLE_H
#define VARIABLE_H
#include <iostream>
#include <string>

using std::string;

class Number;

class Atom;

class Variable {
public:
  Variable(string s):_symbol(s){}
  string _symbol;
  bool _assignable = true;
  string value();
  bool match(Atom *atom);//match for atom
  bool match(Number *num);//match for number
  void setvalue(string s);
  void setassignable();

private:
  string _value;
};
#endif
