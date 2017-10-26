#ifndef ATOM_H
#define ATOM_H

#include <string>
//#include <sstream>
#include "term.h"
using std::string;

class Atom : public Term{
public:
  Atom(string s);//{_symbol = s; }
//private:
  //string _symbol;
};

class Number : public Term{
public:
  Number(double db);/*{
    std::ostringstream strs;
    strs << db;
    _symbol = strs.str();
  }*/
//private:
//  string _symbol;
};

#endif
