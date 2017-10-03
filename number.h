#ifndef NUMBER_H
#define NUMBER_H
#include <string>/*
#include "Variable.h"
#include "Atom.h"*/

using std::string;

class Atom;
class Variable;

class Number{
public:
  Number(int value):_value(value) {}
  string symbol();
  string value();
  bool match(Number num);
  bool match(Number *num);
  bool match(Atom *atom);
  bool match(Variable *x);

private:
  int _value;
  string _symbol;
  bool number_match_or_not_match = false;
  bool number_atom_not_match = false;
  bool number_variable_match = false;

};

#endif
