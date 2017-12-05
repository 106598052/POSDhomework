#include "term.h"
#include "variable.h"
#include "iterator.h"
#include <string>
#include <sstream>
#include <typeinfo>
#include "list.h"
using std::string;
using std::type_info;

//string Term::symbol() const {return _symbol;}
//string Term::value() const {return symbol();}
Iterator * Term::createIterator()
{
  return new NullIterator(this);
}

bool Term::match(Term & a){
  if (typeid(a) ==  typeid(Variable))
  {
    return a.match(*this);
  }
  else if(typeid(a)==typeid(List))
  {
    //List * ps = dynamic_cast<List *>(&a);
    vector<Term *> v,v2;
    v=getvec();
    v2=a.getvec();
    if(v.size()!=v2.size())return false;
    else
    {
      for(int i=0;i<=v.size()-1;i++)
      {
        if(!v[i]->match(*v2[i]))return false;
      }
      return true;
    }
    return symbol() == a.symbol();
  }
  else
  {
    return symbol() == a.symbol();
  }

}
Term::Term ():_symbol(""){}
Term::Term (string s):_symbol(s) {}
Term::Term(double db){
  std::ostringstream strs;
  strs << db;
  _symbol = strs.str();
}
