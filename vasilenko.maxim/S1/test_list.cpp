#define BOOST_TEST_MODULE BiListTests
#include <boost/test/included/unit_test.hpp>
#include "BiList.hpp"

using namespace vasilenko_maxim;

BOOST_AUTO_TEST_CASE(test_bilist_basics)
{
  BiList< int > list;
  BOOST_CHECK(list.empty());

  list.push_back(10);
  list.push_front(5);
  BOOST_CHECK_EQUAL(*list.begin(), 5);

  auto it = list.begin();
  ++it;
  BOOST_CHECK_EQUAL(*it, 10);

  list.pop_back();
  BOOST_CHECK_EQUAL(*list.begin(), 5);
  BOOST_CHECK_EQUAL(list.size(), 1);

  list.clear();
  BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_CASE(test_bidirectional_iterators)
{
  BiList< int > list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

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

BOOST_AUTO_TEST_CASE(test_copy_and_move)
{
  BiList< int > l1;
  l1.push_back(100);
  l1.push_back(200);

  BiList< int > l2 = l1;
  BOOST_CHECK_EQUAL(*l2.begin(), 100);
  BOOST_CHECK_EQUAL(l2.size(), 2);

  BiList< int > l3 = std::move(l1);
  BOOST_CHECK(l1.empty());
  BOOST_CHECK_EQUAL(l3.size(), 2);
  BOOST_CHECK_EQUAL(*l3.begin(), 100);
}

BOOST_AUTO_TEST_CASE(test_clear_and_empty)
{
  BiList< int > lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.clear();
  BOOST_CHECK(lst.empty());
  BOOST_CHECK(lst.size() == 0);
  BOOST_CHECK(lst.begin() == lst.end());
}
