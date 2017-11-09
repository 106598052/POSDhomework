#ifndef VARIABLE_H
#define VARIABLE_H

#include "atom.h"
#include "term.h"
#include <iostream>

class Variable : public Term {
  public:
    Variable(string s):Term(s), _inst(0){}
    string value() const;
    bool match( Term & term );
  private:
    Term * _inst;
};
#endif
