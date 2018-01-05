#ifndef EXP_H
#define EXP_H

#include "atom.h"

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string getResult() = 0;
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }

  bool evaluate(){//回傳match結果
    return _left->match(*_right);
  }

  string getResult() {
    //printf("%s\n","getResult");
    bool legalEva = evaluate();
    ////printf("%s%s\n","legalEva",legalEva);
    if (legalEva && _left->symbol() != _right->symbol()) {//match成功且並不相等
      if (_left->getVariable() != nullptr ){//不是空指標就回傳等於
        return _left->symbol() + " = " + _right->value();
      }
      else if (_right->getVariable() != nullptr ){
        return _left->value() + " = " + _right->symbol();
      }
    }
    else if (legalEva){
      return "true";
    }
    else{
      return "false";
    }
  }

private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }

  string getResult() {
    bool legalEva = evaluate();
    if (legalEva && _left->getResult() == "true" && _right->getResult() == "true"){//去判斷裡面的也都要true
      return "true";
    }
    else if ( legalEva && _left->getResult() ==  _right->getResult()){
      return _left->getResult();
    }
    else if ( legalEva && _left->getResult().find( _right->getResult()) != string::npos ){
      return _left->getResult();
    }
    else if ( legalEva && _left->getResult() == "true" ){
      return _right->getResult();
    }
    else if ( legalEva && _right->getResult() == "true" ){
      return _left->getResult();
    }
    else if(!legalEva){
      return "false";
    }
    else{
      return _left->getResult() + ", " + _right->getResult();
    }
  }

private:
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }

  string getResult() {

   bool legalEva = evaluate();

   if ( _left->getResult() == "true" || _left->getResult() == "false" ){
     return _right->getResult();
   }
   else if ( _right->getResult() == "true" || _right->getResult() == "false" ){
     return _left->getResult();
   }
   else{
     return _left->getResult() + "; " + _right->getResult();
   }
 }

private:
  Exp * _left;
  Exp * _right;
};
#endif
