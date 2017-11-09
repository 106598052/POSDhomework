#ifndef TERM_H
#define TERM_H
#include <string>
#include <sstream>
#include <typeinfo>

using namespace std;

class Term{
public:
  virtual string symbol() const {return _symbol;}
  virtual string value() const {return symbol();}
  virtual bool match(Term & a);
  virtual int arity() const {return 0;}
  virtual Term * args(int index) {throw string("無法使用");}
protected:
  Term ():_symbol(""){}
  Term (string s):_symbol(s) {}
  Term(double db){
    std::ostringstream strs;
    strs << db;
    _symbol = strs.str();
  }
  string _symbol;

};

#endif
