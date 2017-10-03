#ifndef UTTERM_H
#define UTTERM_H
#include "number.h"
#include "atom.h"
#include "variable.h"
#include <iostream>
/*#include "Variable.h"
#include "Atom.h"*/

//test Number.value()
TEST (Number,ctor) {
  Number n(100);
  EXPECT_EQ("100",n.value());
}
//test Number.symbol()
TEST (Number, symbol) {
  Number n(100);
  EXPECT_EQ("100",n.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
  Number n1(25);
  Number n2(25);
  EXPECT_TRUE(n1.match(&n2));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
  Number n1(25);
  Number n2(0);
  EXPECT_FALSE(n1.match(&n2));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
  Number n(25);
  Atom tom("tom");
  EXPECT_FALSE(n.match(&tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
  Number n(25);
  Variable var("X");
  EXPECT_TRUE(n.match(&var));
}
//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
  Atom tom("tom");
  Number n1(25);
  EXPECT_FALSE(tom.match(&n1));
}
// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
  Atom tom("tom");
  Variable var("X");
  ASSERT_TRUE(tom.match(&var));
}
// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
  Variable var("X");
  Atom tom("tom");
  ASSERT_TRUE(var.match(&tom));
  ASSERT_TRUE(tom.match(&var));
}
// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
  Variable var("X");
  Atom jerry("jerry");
  Atom tom("tom");
  ASSERT_TRUE(var.match(&jerry));
  ASSERT_FALSE(tom.match(&var));
}
// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
  Variable var("X");
  Number num(5);
  ASSERT_TRUE(var.match(&num));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
  Variable var("X");
  Number num1(25);
  Number num2(100);
  var.match(&num1);
  ASSERT_FALSE(var.match(&num2));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
  Variable var("X");
  Atom tom("tom");
  Number num(25);
  var.match(&tom);
  ASSERT_FALSE(var.match(&num));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
  Atom tom("tom");
  Variable var("X");
  Number num(25);
  tom.match(&var);
  ASSERT_FALSE(num.match(&var));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
  Variable var("X");
  Atom tom("tom");
  var.match(&tom);
  ASSERT_TRUE(var.match(&tom));
}
#endif
