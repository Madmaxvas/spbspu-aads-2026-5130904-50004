#define BOOST_TEST_MODULE RTreeTests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "RTree.hpp"
#include <string>

namespace vasilenko {

  BOOST_AUTO_TEST_CASE(BasicInsertionAndSearch)
  {
    RTree tree;
    tree.insert(Location{"Base", 0, 0, 10, 10, 0});
    tree.insert(Location{"Camp", 20, 20, 30, 30, 0});

    auto hitsBase = tree.findIntersections(5, 5);
    BOOST_REQUIRE_EQUAL(hitsBase.size(), 1);
    BOOST_CHECK_EQUAL(hitsBase[0]->name, "Base");

    auto miss = tree.findIntersections(15, 15);
    BOOST_CHECK_EQUAL(miss.size(), 0);

    auto hitsCamp = tree.findIntersections(20, 20);
    BOOST_REQUIRE_EQUAL(hitsCamp.size(), 1);
    BOOST_CHECK_EQUAL(hitsCamp[0]->name, "Camp");
  }

  BOOST_AUTO_TEST_CASE(NodeSplittingAndBalancing)
  {
    RTree tree;
    for (int i = 0; i < 10; ++i) {
      std::string name = "Loc_" + std::to_string(i);
      tree.insert(Location{name, i * 10, i * 10, i * 10 + 15, i * 10 + 15, 0});
    }

    auto overlaps = tree.findIntersections(12, 12);
    BOOST_REQUIRE_EQUAL(overlaps.size(), 2);

    bool foundLoc0 = false;
    bool foundLoc1 = false;
    for (std::size_t i = 0; i < overlaps.size(); ++i) {
      if (overlaps[i]->name == "Loc_0") {
        foundLoc0 = true;
      }
      if (overlaps[i]->name == "Loc_1") {
        foundLoc1 = true;
      }
    }
    BOOST_CHECK(foundLoc0 && foundLoc1);
  }

  BOOST_AUTO_TEST_CASE(RTreeIteratorTest)
  {
    RTree tree;
    const int numElements = 15;

    for (int i = 0; i < numElements; ++i) {
      tree.insert(Location{"Point_" + std::to_string(i), i, i, i + 1, i + 1, 0});
    }

    int count = 0;
    for (const auto& loc : tree) {
      BOOST_CHECK(loc.name.find("Point_") != std::string::npos);
      ++count;
    }

    BOOST_CHECK_EQUAL(count, numElements);
  }

}
