#define BOOST_TEST_MODULE ListTests
#include <boost/test/included/unit_test.hpp>
#include "BiList.hpp"

using namespace vasilenko_maxim;

BOOST_AUTO_TEST_CASE(testListBasics)
{
  BiList< int > list;
  BOOST_CHECK(list.empty());
  list.pushBack(10);
  list.pushFront(5);
  BOOST_CHECK_EQUAL(*list.begin(), 5);

  auto it = list.begin();
  ++it;
  BOOST_CHECK_EQUAL(*it, 10);

  list.popBack();
  BOOST_CHECK_EQUAL(*list.begin(), 5);
  BOOST_CHECK_EQUAL(list.size(), 1);

  list.clear();
  BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_CASE(testBidirectionalIterators)
{
  BiList< int > list;
  list.pushBack(1);
  list.pushBack(2);
  list.pushBack(3);

  auto it = list.begin();
  BOOST_CHECK_EQUAL(*it, 1);
  ++it;
  BOOST_CHECK_EQUAL(*it, 2);
  --it;
  BOOST_CHECK_EQUAL(*it, 1);

  it = list.end();
  --it;
  BOOST_CHECK_EQUAL(*it, 3);
  --it;
  BOOST_CHECK_EQUAL(*it, 2);
}

BOOST_AUTO_TEST_CASE(testCopyAndMove)
{
  BiList< int > l1;
  l1.pushBack(100);
  l1.pushBack(200);

  BiList< int > l2 = l1;
  BOOST_CHECK_EQUAL(*l2.begin(), 100);
  BOOST_CHECK_EQUAL(l2.size(), 2);

  BiList< int > l3 = std::move(l1);
  BOOST_CHECK(l1.empty());
  BOOST_CHECK_EQUAL(l3.size(), 2);
  BOOST_CHECK_EQUAL(*l3.begin(), 100);
}
