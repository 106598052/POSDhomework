#ifndef NUMBER_H_INCLUDED
#define NUMBER_H_INCLUDED

#include "term.h"

class Number : public Term{
public:
  Number(double db):Term(db) {} 
};
#endif
