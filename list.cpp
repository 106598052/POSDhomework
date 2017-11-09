#include "list.h"
#include "variable.h"
#include <typeinfo>

string List::symbol() const{
  string ret ="[";
  if(_elements.size() != 0){
    for(int i = 0; i < _elements.size() - 1 ; i++){
      ret += _elements[i]-> symbol() + ", ";
    }
    ret += _elements[_elements.size()-1]-> symbol();
  }
  ret += "]";
  return  ret;
}

string List::value() const{
  string ret ="[";
  if(_elements.size() != 0){
    for(int i = 0; i < _elements.size() - 1 ; i++){
      ret += _elements[i]-> value() + ", ";
    }
    if(_elements.size() != 0)
    ret += _elements[_elements.size()-1]-> value();
  }
  ret += "]";
  return  ret;
}

Term * List::head() const{
  if(this->getSize() == 0)  throw string("Accessing head in an empty list");
  vector<Term *> vec = _elements;
  return vec.front();
}

List * List::tail() const{
  if(this->getSize() == 0) throw string("Accessing tail in an empty list");
  List * list = new List();
  list->_elements = _elements;
  list->_elements.erase(list->_elements.begin());
  return list;
}

bool List::match(Term & term){
  bool ret = false;
  if(typeid(term) == typeid(Variable)){ //match var 機制
    ret = term.match(*this);
  }else if(_elements.size() != 0){  //match list 機制
    List *pt = dynamic_cast<List *>(&term);
    if(pt){
      ret = ComparisonList(pt);
    }
  }
  return ret;
}

int List::getSize() const{
  return _elements.size();
}

bool List::ComparisonList(List *list){
  if(_elements.size() != list->getSize()) return false;
  for(int i = 0; i < _elements.size(); i++){
    if(!(_elements[i]->match(*(list->_elements[i])))) return false;
  }
  return true;
}
