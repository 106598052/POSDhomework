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
  Term ():_symbol(""){} //預設建構子
  Term (string s):_symbol(s) {} //帶string參建構子，初始化 _symbol
  //帶double參數建構子，透過stream將小數補0移除
  Term(double db){
    std::ostringstream strs;
    strs << db;
    _symbol = strs.str();
  }
  string _symbol;

};

#endif
