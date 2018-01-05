#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include <stack>

using std::stack;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms() {}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    //printf("token:%d\n",_currentToken);
    if(token == VAR){
      //printf("%s\n","token == VAR");
      for (int i = 0; i < _varVector.size(); i++) {
        //printf("%s\n","_varVector != null");
        if ( symtable[_scanner.tokenValue()].first == _varVector[i]->symbol()){
          //printf("%s\n","_varVector has the same var");
          return _varVector[i];
        }
      }
      //printf("%s\n","_varVector don't has the same var");
      Variable *var = new Variable(symtable[_scanner.tokenValue()].first);
      _varVector.push_back(var);
      return var;
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }
    return nullptr;
  }

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("Unbalanced operator");//不符合
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      if(args.size()==0){
        return new Atom("[]");
      }
      return new List(args);
    } else {
      throw string("Unbalanced operator");//不符合
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void buildExpression(){
    // createTerm();
    //printf("%s\n","buildExpression start disjunctionMatch");
    disjunctionMatch();
    //printf("%s\n","buildExpression restDisjunctionMatch");
    restDisjunctionMatch();
    if (createTerm()  != nullptr || _currentToken != '.'){
      //printf("LINE96 %d\n",_currentToken);
      throw string("Missing token '.'");
    }
  }

  void disjunctionMatch() {
    //printf("%s\n","disjunctionMatch start conjunctionMatch");
    conjunctionMatch();
    //printf("%s\n","disjunctionMatch start restConjunctionMatch");
    restConjunctionMatch();
  }

  void conjunctionMatch() {
    //printf("%s\n","start conjunctionMatch");
    Term * left = createTerm();
    //printf("LINE113 left:%s\n",left->symbol());
    if (createTerm() == nullptr && _currentToken == '=') {
      //printf("%s\n","createTerm() == nullptr && _currentToken == '='");
      Term * right = createTerm();
      //printf("LINE117 right:%s\n",right->symbol());
      _expStack.push(new MatchExp(left, right));
    }
    else if ( _currentToken == '.' )  {
      throw string( left->symbol() + " does never get assignment");
    }
    else if ( _currentToken == ';' || _currentToken == ',' ){
      throw string( "Unexpected '" + string(1, _currentToken) + "' before '" +  _scanner.currentChar()+"'");
    }
  }

  void restDisjunctionMatch() {
    if (_scanner.currentChar() == ';') {
      _varVector.clear();//初始化
      createTerm();
      //printf("%s\n","restDisjunctionMatch start disjunctionMatch");
      _scanner.peekNextToken();
      if (_scanner.tokenValue() == NONE ){//偷看下一個
        throw string ( "Unexpected ';' before '.'");
      }
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      //printf("%s\n","restDisjunctionMatch start restDisjunctionMatch");
      restDisjunctionMatch();
    }
  }

  void restConjunctionMatch() {
    //printf("%s\n","start restConjunctionMatch");
    if (_scanner.currentChar() == ',') {
      createTerm();
      _scanner.peekNextToken();//偷看下一個是不是空值
      if(_scanner.tokenValue() == NONE){
        throw string ( "Unexpected ',' before '.'");
      }
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }

  Exp* getExpressionTree(){
    return _expStack.top();
  }

  string result() {
    return getExpressionTree()->getResult() + ".";
  }

private:/*
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
  FRIEND_TEST(ParserTest, createTerms);
*/
  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  //MatchExp* _root;
  stack<Exp*> _expStack;
  vector<Variable *> _varVector;
};
#endif
