#include <list>
#include "Shapes.h"
#include <algorithm>

using namespace std;

bool IncreasingPerimeter (Shape * a, Shape *b)
{
  return a->perimeter() < b->perimeter();
}
bool DecreasingPerimeter (Shape * a, Shape *b)
{
  return a->perimeter() > b->perimeter();
}
bool IncreasingArea (Shape * a, Shape *b)
{
  return a->area() < b->area();
}
bool DecreasingArea (Shape * a, Shape *b)
{
  return a->area() > b->area();
}
bool IncreasingCompactness (Shape * a, Shape *b)
{
  return ( a->area() / a->perimeter() ) < ( b->area() / b->perimeter() );
}

class Sort {

  public :static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList)
  {
    shapeList->sort(IncreasingPerimeter);
  }

  public :static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList)
  {
    shapeList->sort(DecreasingPerimeter);
  }
  public :static void sortByIncreasingArea(std::list<Shape *> * shapeList)
  {
    shapeList->sort(IncreasingArea);
  }

  public :static void sortByDecreasingArea(std::list<Shape *> * shapeList)
  {
    shapeList->sort(DecreasingArea);
  }

  public :static void sortByIncreasingCompactness(std::list<Shape *> * shapeList)
  {
    // Compactness = area/perimeter
    shapeList->sort(IncreasingCompactness);
  }
};
