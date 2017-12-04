#ifndef STRUCT_H
#define STRUCT_H

#include "term.h"
#include "atom.h"
#include <vector>
#include <string>

using std::string;

class Iterator;
class Struct: public Term {
public:
  Struct(Atom name, std::vector<Term *> args): _name(name) {
    _args = args;
  }//Atom name => Term name

  Term * args(int index) {
    return _args[index];
  }
  int arity()
  {
    return _args.size();
  }
  Atom & name() {
    return _name;
  }
  string symbol() const {
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    if(!_args.empty())
    {
      for (; it != _args.end()-1; ++it)
        ret += (*it)->symbol()+", ";
      ret  += (*it)->symbol()+")";
    }
    else
    {
      ret+=")";
    }
    return ret;
  }
  string value() const {
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->value()+", ";
    ret  += (*it)->value()+")";
    return ret;
  }
  Iterator * createIterator();
  Iterator * createDFSIterator();
  Iterator * createBFSIterator();
private:
  Atom _name;
  std::vector<Term *> _args;
};

#endif
