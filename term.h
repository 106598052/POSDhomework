#ifndef TERM_H
#define TERM_H

#include <string>
#include <sstream>
#include <typeinfo>
#include <iostream>
#include <vector>
#include <stdexcept>
//#include "atom.h"
//#include "variable.h"
class Variable;
class Iterator;
using namespace std;

class Term{
public:
  virtual string symbol() const{return _symbol;}
  virtual string value() const{return symbol();}
  virtual Term *getinst(){return nullptr;}
  virtual Iterator * createIterator();
  virtual Term * args(int index)
  {
    return nullptr;
  }
  virtual int arity()
  {
    return 0;
  }
  virtual bool match(Term & a);//{
    /*if (typeid(a) ==  typeid(Variable))
      return a.match(*this);
    else*/
      //return symbol() == a.symbol();
  //}
  virtual std::vector<Term *> getvec()
  {
    vector<Term *> v;
    return v;
  }
protected:
  Term ();
  Term (string s);
  Term(double db);
  string _symbol;
};

#endif
