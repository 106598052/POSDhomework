#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <string>
#include <vector>
#include <typeinfo>
#include "atom.h"
using std::vector;

class Iterator;
class List : public Term {
public:
  string symbol() const
  {
    return value();
  }
  string value() const
  {
    string s="[";
    if(_elements.size()>0)
    {
      for(int i=0;i<_elements.size()-1;i++)
      {
        s+=_elements[i]->value();
        s+=", ";
      }
      s+=_elements[_elements.size()-1]->value();
      s+="]";
    }
    else s+="]";
    return s;
  }
  List ()
  {

  }
  List (vector<Term *> const & elements):_elements(elements)
  {
  }
  Term * head() const
  {
    if(_elements.size()==0)
    {
      //return new Atom("fail");
      throw string("Accessing head in an empty list");
    }
    return _elements[0];
  }
  List * tail() const
  {
    if(_elements.size()==0)
    {
      //return new List;
      throw string("Accessing tail in an empty list");
      //throw new string("Accessing tail in an empty list");
    }
    List *l=new List();
    l->_elements=_elements;
    if(l->_elements.size()>0)l->_elements.erase(l->_elements.begin());
    return l;
  }
  vector<Term *> getvec()
  {
    return _elements;
  }
  Term * args(int index) {
    return _elements[index];
  }
  int arity() const {
    return _elements.size();
  }
  Iterator * createDFSIterator();
  Iterator * createBFSIterator();
private:
  vector<Term *> _elements;

};

#endif
