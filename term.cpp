#include "term.h"
#include "variable.h"

bool Term::match(Term & a){
  //對於var做額外處理
  if (typeid(a) ==  typeid(Variable))
    return a.match(*this); //若對象為var，將自己丟入var，var必須自行時做match
  else
    return symbol() == a.symbol(); //其餘的simple object皆是比較 value與symbol值同意
}
