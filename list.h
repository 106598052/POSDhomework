#ifndef LIST_H
#define LIST_H

#include "atom.h"

#include <vector>
using std::vector;

class List : public Term {
public:
  string symbol() const{
    string result = "[";
    if(_elements.size()>0){
      for(int i=0; i<_elements.size()-1;i++){
        result = result + _elements[i]->value() + ", ";
      }
      result = result + _elements[_elements.size()-1]->value();
    }
    result = result + "]";
    return result;
  };
  string value() const{return symbol();};
  //bool match(Term & term){};
  List ()/*: _elements() */{_symbol="[]";}

  List (vector<Term *>  & elements):_elements(elements){}
  Term * head() const{
    if(_elements.size()==0){
      throw string("Accessing head in an empty list");
    }
    else{
      return _elements[0];
    }
  }
  List * tail() const{
    if(_elements.size()==0){
      throw string("Accessing tail in an empty list");
    }
    else{
      List *l=new List();
      l->_elements=_elements;
      l->_elements.erase(l->_elements.begin());
      return l;
    }
  }

  vector<Term *> getvec()
  {
    return _elements;
  }
private:
  vector<Term *> _elements;

};

#endif
