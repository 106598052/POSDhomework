#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
using namespace std;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "list.h"
#include "scanner.h"
#include "struct.h"
#include "number.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
  Term* createTerm(){
    if(_scanner.isEmpty()){return nullptr;}
    int token = _scanner.nextToken();
    //std::cout << token << '\n';
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
        Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
        if(_scanner.currentChar() == '(' ) {
          _scanner.nextToken() ;
          vector<Term*> terms = getArgs();
          if(_currentToken == ')'){
            return new Struct(*atom, terms);
          }
        }
        else{
          return atom;
        }
    }
    else if(token == 91){
      vector<Term*> terms = getArgs();
      if(_currentToken == 93){
        return new List(terms);
      }
      else if(_currentToken == ')'){
        throw string("unexpected token");
      }
    }

    return nullptr;
  }

  vector<Term*> getArgs(){
    Term* term = createTerm();
    vector<Term*> args;
    if(term)
      args.push_back(term);
    if(term != nullptr ||(_currentToken != ']' &&  _currentToken != ')')){
      while((_currentToken = _scanner.nextToken()) == ',') {
        args.push_back(createTerm());
      }
    }
    return args;
  }



private:
  Scanner _scanner;
  int _currentToken;
};
#endif
