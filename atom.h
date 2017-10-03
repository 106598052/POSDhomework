#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;

class Number;

class Variable;

class Atom {
public:
  Atom(string s):_symbol(s) {}
  //bool operator(Atom a, Atom b)
  //因為在物件中已經有自己所以只要讀入一個參數
  bool operator == /*C++中 overload operator ==*/(Atom a);
  bool match(Number *number);
  bool match(Variable *X);
  string _symbol;
private:
  bool MATCH_ATOM_TO_NUMBER_FAILURE = false;
};

#endif
