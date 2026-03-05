#define BOOST_TEST_MODULE ListTests
#include <boost/test/included/unit_test.hpp>
#include <utility>
#include "list.hpp"

using namespace vasilenko_maxim;

BOOST_AUTO_TEST_CASE(test_push_and_pop)
{
  List< int > list;
  BOOST_CHECK(list.isEmpty());

  list.pushBack(10);
  list.pushFront(5);
  BOOST_CHECK_EQUAL(list.front(), 5);
  BOOST_CHECK_EQUAL(list.back(), 10);

  list.popFront();
  BOOST_CHECK_EQUAL(list.front(), 10);
  list.popBack();
  BOOST_CHECK(list.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_rule_of_five)
{
  List< int > l1;
  l1.pushBack(1);
  l1.pushBack(2);

  List< int > l2(l1);
  BOOST_CHECK_EQUAL(l2.front(), 1);
  BOOST_CHECK_EQUAL(l2.back(), 2);

  List< int > l3(std::move(l1));
  BOOST_CHECK(l1.isEmpty());
  BOOST_CHECK_EQUAL(l3.front(), 1);
}
