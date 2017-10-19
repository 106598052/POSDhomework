#ifndef UTVARIABLE_H
#define UTVARIABLE_H
#include "variable.h"
#include "struct.h"
#include "atom.h"
#include "number.h"

TEST(Variable, constructor){
  Variable X("X");
  ASSERT_EQ("X", X._symbol);
}

TEST(Variable , matching){
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ( "tom", X.value());
}

TEST (Variable , haveValue){
  Atom tom ("tom");
  Atom jerry ("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable , numE_to_varX){
  Variable varX("X");
  Number num1(2.7182);
  varX.match(num1);
  num1.value();
  ASSERT_EQ("2.7182",num1.value());
}

// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
  Variable varX("X");
  Variable varY("Y");
  Number num1(1);
  varX.match(varY);
  varX.match(num1);
  EXPECT_EQ("1",varX.value());
  EXPECT_EQ("1",varY.value());
}

// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
  Variable varX("X");
  Variable varY("Y");
  Number num1(1);
  varX.match(varY);
  varY.match(num1);
  EXPECT_EQ("1",varX.value());
  EXPECT_EQ("1",varY.value());
}

// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
  Variable varX("X");
  Number num1(1);
  varX.match(varX);
  varX.match(num1);
  EXPECT_EQ("1",varX.value());
}

// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
  Variable varY("Y");
  Number num1(1);
  varY.match(num1);
  Variable varX("X");
  varX.match(varY);
  EXPECT_EQ("1",varX.value());
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
  Variable varX("X");
  Variable varY("Y");
  Variable varZ("Z");
  Number num1(1);
  varX.match(varY);
  varY.match(varZ);
  varZ.match(num1);
  EXPECT_EQ("1",varX.value());
  EXPECT_EQ("1",varY.value());
  EXPECT_EQ("1",varZ.value());
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
  Variable varX("X");
  Variable varY("Y");
  Variable varZ("Z");
  Number num1(1);
  varX.match(varY);
  varX.match(varZ);
  varZ.match(num1);
  EXPECT_EQ("1",varX.value());
  EXPECT_EQ("1",varY.value());
  EXPECT_EQ("1",varZ.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST (Variable, Struct1) {
  Variable varX("X");
  std::vector<Term *> v = {&varX};
  Struct s(Atom("s"),v);
  Variable varY("Y");
  varY.match(s);
  EXPECT_EQ("Y",varY.symbol());
  EXPECT_EQ("s(X)",varY.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {
  Variable varX("X");
  std::vector<Term *> v = {&varX};
  Struct s(Atom("s"),v);
  Variable varY("Y");
  varY.match(s);
  Atom teddy("teddy");
  varY.match(teddy);
  EXPECT_EQ("Y",varY.symbol());
  EXPECT_EQ("s(teddy)",varY.value());
}
/*

TEST (Variable, TAtest) {
  Variable varX("X");
  Variable varY("Y");
  Number num(1);
  varY.match(varX);
  EXPECT_EQ("Y",varX.value());
  num.match(varX);
  EXPECT_EQ("Y",varX.value());
}*/
#endif
