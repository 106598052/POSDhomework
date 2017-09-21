#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
#include <iostream>
TEST (Sort, sortByIncreasingPerimeter) {
  Circle cir1(0,0,10,"circle1");
  Rectangle rect1(0,0,2,10,"rectangle1");
  vertex v1,v2,v3;
  v1.x=0;
  v1.y=0;
  v2.x=3;
  v2.y=0;
  v3.x=0;
  v3.y=4;
  Triangle tri1 (v1,v2,v3,"triangle1");
  std::list<Shape *> shapeList ;
  shapeList.push_back(&cir1);
  shapeList.push_back(&rect1);
  shapeList.push_back(&tri1);
  Sort :: sortByIncreasingPerimeter(&shapeList);
  std::list<Shape *>:: iterator iter=shapeList.begin();
  ASSERT_EQ(tri1.getShapeName(),(*iter)->getShapeName());
  iter++;
  ASSERT_EQ(rect1.getShapeName(),(*iter)->getShapeName());
  iter++;
  ASSERT_EQ(cir1.getShapeName(),(*iter)->getShapeName());
}

TEST (Sort, sortByDecreasingPerimeter) {
  Circle cir1(0,0,10,"circle1");
  Rectangle rect1(0,0,2,10,"rectangle1");
  vertex v1,v2,v3;
  v1.x=0;
  v1.y=0;
  v2.x=3;
  v2.y=0;
  v3.x=0;
  v3.y=4;
  Triangle tri1 (v1,v2,v3,"triangle1");
  std::list<Shape *> shapeList ;
  shapeList.push_back(&cir1);
  shapeList.push_back(&rect1);
  shapeList.push_back(&tri1);
  Sort :: sortByDecreasingPerimeter(&shapeList);
  std::list<Shape *>:: iterator iter=shapeList.begin();
  ASSERT_EQ(cir1.getShapeName(),(*iter)->getShapeName());
  iter++;
  ASSERT_EQ(rect1.getShapeName(),(*iter)->getShapeName());
  iter++;
  ASSERT_EQ(tri1.getShapeName(),(*iter)->getShapeName());
}

TEST (Sort, sortByIncreasingArea) {
  Circle cir1(0,0,10,"circle1");
  Rectangle rect1(0,0,2,10,"rectangle1");
  vertex v1,v2,v3;
  v1.x=0;
  v1.y=0;
  v2.x=3;
  v2.y=0;
  v3.x=0;
  v3.y=4;
  Triangle tri1 (v1,v2,v3,"triangle1");
  std::list<Shape *> shapeList ;
  shapeList.push_back(&cir1);
  shapeList.push_back(&rect1);
  shapeList.push_back(&tri1);
  Sort :: sortByIncreasingArea(&shapeList);
  std::list<Shape *>:: iterator iter=shapeList.begin();
  ASSERT_EQ(tri1.getShapeName(),(*iter)->getShapeName());
  iter++;
  ASSERT_EQ(rect1.getShapeName(),(*iter)->getShapeName());
  iter++;
  ASSERT_EQ(cir1.getShapeName(),(*iter)->getShapeName());
}

TEST (Sort, sortByDecreasingArea) {
  Circle cir1(0,0,10,"circle1");
  Rectangle rect1(0,0,2,10,"rectangle1");
  vertex v1,v2,v3;
  v1.x=0;
  v1.y=0;
  v2.x=3;
  v2.y=0;
  v3.x=0;
  v3.y=4;
  Triangle tri1 (v1,v2,v3,"triangle1");
  std::list<Shape *> shapeList ;
  shapeList.push_back(&cir1);
  shapeList.push_back(&rect1);
  shapeList.push_back(&tri1);
  Sort :: sortByDecreasingArea(&shapeList);
  std::list<Shape *>:: iterator iter=shapeList.begin();
  ASSERT_EQ(cir1.getShapeName(),(*iter)->getShapeName());
  iter++;
  ASSERT_EQ(rect1.getShapeName(),(*iter)->getShapeName());
  iter++;
  ASSERT_EQ(tri1.getShapeName(),(*iter)->getShapeName());
}

TEST (Sort, sortByIncreasingCompactness) {
  Circle cir1(0,0,10,"circle1");
  Rectangle rect1(0,0,2,10,"rectangle1");
  vertex v1,v2,v3;
  v1.x=0;
  v1.y=0;
  v2.x=3;
  v2.y=0;
  v3.x=0;
  v3.y=4;
  Triangle tri1 (v1,v2,v3,"triangle1");
  std::list<Shape *> shapeList ;
  shapeList.push_back(&cir1);
  shapeList.push_back(&rect1);
  shapeList.push_back(&tri1);
  Sort :: sortByIncreasingCompactness(&shapeList);
  std::list<Shape *>:: iterator iter=shapeList.begin();
  ASSERT_EQ(tri1.getShapeName(),(*iter)->getShapeName());
  iter++;
  ASSERT_EQ(rect1.getShapeName(),(*iter)->getShapeName());
  iter++;
  ASSERT_EQ(cir1.getShapeName(),(*iter)->getShapeName());
}
#endif
