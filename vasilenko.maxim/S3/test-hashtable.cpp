#include <boost/test/unit_test.hpp>
#include "HashTable.hpp"
#include "SipHash.hpp"
#include "Equal.hpp"

BOOST_AUTO_TEST_SUITE(HashTableTestSuite)

BOOST_AUTO_TEST_CASE(TestAddAndHas)
{
  vasilenko::HashTable< std::pair<std::string, std::string>, int, vasilenko::PairHash, vasilenko::PairEqual > ht(20);
  std::pair<std::string, std::string> p("a", "b");
  ht.add(p, 42);
  BOOST_CHECK(ht.has(p));
}

BOOST_AUTO_TEST_CASE(TestDrop)
{
  vasilenko::HashTable< std::pair<std::string, std::string>, int, vasilenko::PairHash, vasilenko::PairEqual > ht(20);
  std::pair<std::string, std::string> p("x", "y");
  ht.add(p, 10);
  BOOST_CHECK(ht.has(p));
  ht.drop(p);
  BOOST_CHECK(!ht.has(p));
}

BOOST_AUTO_TEST_SUITE_END()
