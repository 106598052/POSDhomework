#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <vector>
using std::vector;

class List : public Term {
public:
  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}
  string symbol() const;
  string value() const;
  bool match(Term & term);
  Term * head() const; //使用pointer的用意?
  List * tail() const;
  bool ComparisonList(List *list);
  int getSize() const;
  vector<Term *> _elements; //有時間將他變保護
};

#endif
