#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "term.h"
#include "struct.h"
#include "atom.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  List L;
  EXPECT_EQ("[]",L.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
  Number num1(8128);
  Number num2(496);
  vector<Term *> args = {&num1,&num2};
  List l(args);
  EXPECT_EQ("[8128, 496]", l.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom atom1("terence_tao");
  Atom atom2("alan_mathison_turing");
  vector<Term *> args = {&atom1,&atom2};
  List l(args);
  EXPECT_EQ("[terence_tao, alan_mathison_turing]", l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable var1("X");
  Variable var2("Y");
  vector<Term *> args = {&var1,&var2};
  List l(args);
  EXPECT_EQ("[X, Y]", l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Number num(496);
  Variable var("X");
  Atom atom("terence_tao");
  vector<Term *> args = {&num,&var,&atom};
  List l(args);
  Atom tom("tom");
  EXPECT_FALSE(tom.match(l));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number num1(496);
  Variable var("X");
  Atom atom("terence_tao");
  vector<Term *> args = {&num1,&var,&atom};
  List l(args);
  Number num2(8128);
  EXPECT_FALSE(num2.match(l));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Variable var("X");
  vector<Term *> args={&var};
  Struct s(Atom("s"),args);
  Number num(496);
  Atom atom("terence_tao");
  vector<Term *> args2 = {&num,&var,&atom};
  List l(args2);
  EXPECT_FALSE(s.match(l));
  EXPECT_FALSE(l.match(s));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Variable var1("Y");
  Number num(496);
  Variable var2("X");
  Atom atom("terence_tao");
  vector<Term *> args = {&num,&var2,&atom};
  List l(args);
  EXPECT_TRUE(var1.match(l));
  EXPECT_TRUE(l.match(var1));
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Number num(496);
  Variable var("X");
  Atom atom("terence_tao");
  vector<Term *> args = {&num,&var,&atom};
  List l(args);
  EXPECT_TRUE(var.match(l));
  //EXPECT_TRUE(l.match(var));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Number num(496);
  Variable var("X");
  Atom atom("terence_tao");
  vector<Term *> args = {&num,&var,&atom};
  List l1(args);
  List l2(args);
  EXPECT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Number num(496);
  Variable var1("X");
  Atom atom("terence_tao");
  vector<Term *> args1 = {&num,&var1,&atom};
  List l1(args1);
  Variable var2("Y");
  vector<Term *> args2 = {&num,&var2,&atom};
  List l2(args2);
  EXPECT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Number num1(496);
  Variable var("X");
  Atom atom("terence_tao");
  vector<Term *> args1 = {&num1,&var,&atom};
  List l1(args1);
  Number num2(8128);
  vector<Term *> args2 = {&num1,&num2,&atom};
  List l2(args2);
  l2.match(l1);
  EXPECT_EQ("8128",var.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Number num(496);
  Variable var1("X");
  Atom atom1("terence_tao");
  vector<Term *> args = {&num,&var1,&atom1};
  List l(args);
  Variable var2("Y");
  l.match(var2);
  Atom atom2("alan_mathison_turing");
  var1.match(atom2);
  //atom2.match(var1);
  EXPECT_EQ("[496, alan_mathison_turing, terence_tao]",var2.value());
  EXPECT_EQ("alan_mathison_turing",var1.value());
}

// Example:
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("[first]"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ(string("[first]"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
  EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  vector<Term *> args;
  List l(args);
  try
  {
    l.head()->symbol();
  }
  catch(string e){}
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  vector<Term *> args;
  List l(args);
  try
  {
    l.tail()->symbol();
  }
  catch(string e){}
}




#endif
