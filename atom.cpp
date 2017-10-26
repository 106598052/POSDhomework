#include "atom.h"
#include <string>
#include <sstream>
#include "term.h"
using std::string;

Atom::Atom(string s){_symbol = s; }
/*
Number::Number(double db){
  std::ostringstream strs;
  strs << db;
  _symbol = strs.str();
}*/
