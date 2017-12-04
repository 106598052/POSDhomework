#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"
TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    // StructIterator it(&s);
    Iterator *itStruct = s.createIterator();
    // Iterator& itStruct = it;
    // ASSERT_EQ(it.first()->symbol());
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

//s(1, t(X, 2), Y)
TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator *it = s.createIterator();
  it->first();
  it->next();
  Struct *s2 = dynamic_cast<Struct *>(it->currentItem());

  StructIterator it2(s2);
  it2.first();
  ASSERT_EQ("X", it2.currentItem()->symbol());
  ASSERT_FALSE(it2.isDone());
  it2.next();
  ASSERT_EQ("2", it2.currentItem()->symbol());
  ASSERT_FALSE(it2.isDone());
  it2.next();
  ASSERT_TRUE(it2.isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    ListIterator it(&l);
    Iterator* itList = &it;
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
  Number one(1);
  NullIterator nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator * it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

// s(1, t(X, 2), Y)
TEST(iterator, structFirstDFS) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator *it = s.createDFSIterator();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, listFirstDFS) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  // Struct t(Atom("t"), { &X, &two });
  // Struct s(Atom("s"), { &one, &t, &Y });
  List l({&X,&Y,&one,&two});
  List l2({&two,&l,&X});
  Iterator *it = l2.createDFSIterator();
  it->first();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[X, Y, 1, 2]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

//S(1, t(X, 2, [X, Y]), Y)
TEST(iterator, structSecondDFS) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  List l({&X,&Y});
  Struct t(Atom("t"), { &X, &two,&l });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator *it = s.createDFSIterator();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2, [X, Y])", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[X, Y]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

//[X, Y, t(X, 2), []]
TEST(iterator, ListSecondDFS) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  List l2;
  List l({&X,&Y, &t, &l2});
  Iterator *it = l.createDFSIterator();
  it->first();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[]", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

// s(1, t(X, 2), Y)
TEST(iterator, StructFirstBFS) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator *it = s.createBFSIterator();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

//[2, [X, Y], 1]
TEST(iterator, listFirstBFS) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  List l({&X,&Y});
  List l2({&two,&l,&one});
  Iterator *it = l2.createBFSIterator();
  it->first();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[X, Y]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

//S(1, t(X, 2, [X, Y]), Y)
TEST(iterator, StructSecondBFS) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  List l({&X,&Y});
  Struct t(Atom("t"), { &X, &two,&l });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator *it = s.createBFSIterator();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2, [X, Y])", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[X, Y]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}
//[X, Y, t(X, 2), []]
TEST(iterator, ListSecondBFS) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  List l2;
  List l({&X,&Y, &t, &l2});
  Iterator *it = l.createBFSIterator();
  it->first();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}


#endif