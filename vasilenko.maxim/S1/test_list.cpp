#include "list.hpp"
#include <iostream>
#include <utility>

namespace {

void testPushBackAndFront()
{
  vasilenko_maxim::List<int> lst;
  lst.pushBack(20);
  lst.pushFront(10);

  if (lst.front() != 10) {
    std::cerr << "testPushBackAndFront failed on front" << "\n";
    std::exit(2);
  }
  if (lst.back() != 20) {
    std::cerr << "testPushBackAndFront failed on back" << "\n";
    std::exit(2);
  }
}

void testPopFrontBack()
{
  vasilenko_maxim::List<int> lst;
  lst.pushBack(1);
  lst.pushBack(2);
  lst.pushBack(3);
  lst.popFront();

  if (lst.front() != 2) {
    std::cerr << "testPopFront failed" << "\n";
    std::exit(2);
  }

  lst.popBack();
  if (lst.back() != 2) {
    std::cerr << "testPopBack failed" << "\n";
    std::exit(2);
  }
}

void testCopyMove()
{
  vasilenko_maxim::List<int> lst1;
  lst1.pushBack(1);

  vasilenko_maxim::List<int> lst2(lst1);
  if (lst2.front() != 1) {
    std::cerr << "testCopy failed" << "\n";
    std::exit(2);
  }

  vasilenko_maxim::List<int> lst3(std::move(lst1));
  if (lst3.front() != 1 || !lst1.isEmpty()) {
    std::cerr << "testMove failed" << "\n";
    std::exit(2);
  }
}

void testClear()
{
  vasilenko_maxim::List<int> lst;
  lst.pushBack(1);
  lst.clear();

  if (!lst.isEmpty()) {
    std::cerr << "testClear failed" << "\n";
    std::exit(2);
  }
}

}

int main()
{
  testPushBackAndFront();
  testPopFrontBack();
  testCopyMove();
  testClear();

  std::cout << "All tests passed" << "\n";

  return 0;
}
