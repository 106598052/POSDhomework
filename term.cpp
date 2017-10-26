#include "term.h"
#include "variable.h"
#include <string>
#include <sstream>
#include <typeinfo>
#include <iostream>
#include "list.h"

using std::string;
using std::type_info;
using namespace std;

//string Term::symbol() const {return _symbol;}
//string Term::value() const {return symbol();}
bool Term::match(Term & a){
  if (typeid(a) ==  typeid(Variable)){
    return a.match(*this);
  }
  else if(typeid(a) == typeid(List)){
    bool result = true;
    vector<Term *> vec1,vec2;
    vec1 = getvec();
    vec2 = a.getvec();
    if(vec1.size()!=vec2.size()){
      result = false;
    }
    else{
      for(int i=0;i<vec1.size();i++){
        if(!vec1[i]->match(*vec2[i])){
          result = false;
          break;
        }
      }
    }
    return result;
  }
  else{
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
