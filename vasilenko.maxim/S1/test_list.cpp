#define BOOST_TEST_MODULE BilistTests
#include <boost/test/included/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_CASE(test_bilist_basics)
{
  vasilenko_maxim::Bilist< int > list;
  BOOST_CHECK(list.isEmpty());

  list.pushBack(10);
  list.pushFront(5);
  BOOST_CHECK_EQUAL(list.front(), 5);
  BOOST_CHECK_EQUAL(list.back(), 10);

  list.popBack();
  BOOST_CHECK_EQUAL(list.back(), 5);

  list.clear();
  BOOST_CHECK(list.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_bidirectional_iterators)
{
  vasilenko_maxim::Bilist< int > list;
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
}

BOOST_AUTO_TEST_CASE(test_copy_and_move)
{
  vasilenko_maxim::Bilist< int > l1;
  l1.pushBack(100);

  vasilenko_maxim::Bilist< int > l2 = l1;
  BOOST_CHECK_EQUAL(l2.front(), 100);

  vasilenko_maxim::Bilist< int > l3 = std::move(l1);
  BOOST_CHECK(l1.isEmpty());
  BOOST_CHECK_EQUAL(l3.front(), 100);
}
