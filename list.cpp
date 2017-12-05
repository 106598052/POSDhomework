#include "list.h"
#include "iterator.h"
#include "term.h"
Iterator * List::createDFSIterator()
{
  return new DFSIterator(this);
}

Iterator * List::createBFSIterator()
{
  return new BFSIterator(this);
}
