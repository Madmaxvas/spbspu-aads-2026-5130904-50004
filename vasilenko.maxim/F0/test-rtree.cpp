#include "RTree.hpp"
#include <cassert>
#include <iostream>
#include <string>

namespace vasilenko {

  void testBasicInsertionAndSearch()
  {
    RTree tree;
    tree.insert(Location{"Base", 0, 0, 10, 10, 0});
    tree.insert(Location{"Camp", 20, 20, 30, 30, 0});

    auto hitsBase = tree.findIntersections(5, 5);
    assert(hitsBase.size() == 1);
    assert(hitsBase[0]->name == "Base");

    auto miss = tree.findIntersections(15, 15);
    assert(miss.size() == 0);

    auto hitsCamp = tree.findIntersections(20, 20);
    assert(hitsCamp.size() == 1);
    assert(hitsCamp[0]->name == "Camp");

    std::cout << "[OK] testBasicInsertionAndSearch passed.\n";
  }

  void testNodeSplittingAndBalancing()
  {
    RTree tree;
    for (int i = 0; i < 10; ++i) {
      std::string name = "Loc_" + std::to_string(i);
      tree.insert(Location{name, i * 10, i * 10, i * 10 + 15, i * 10 + 15, 0});
    }

    auto overlaps = tree.findIntersections(12, 12);
    assert(overlaps.size() == 2);

    bool foundLoc0 = false;
    bool foundLoc1 = false;
    for (std::size_t i = 0; i < overlaps.size(); ++i) {
      if (overlaps[i]->name == "Loc_0") foundLoc0 = true;
      if (overlaps[i]->name == "Loc_1") foundLoc1 = true;
    }
    assert(foundLoc0 && foundLoc1);

    std::cout << "[OK] testNodeSplittingAndBalancing passed.\n";
  }

  void testRTreeIterator()
  {
    RTree tree;
    const int numElements = 15;

    for (int i = 0; i < numElements; ++i) {
      tree.insert(Location{"Point_" + std::to_string(i), i, i, i + 1, i + 1, 0});
    }

    int count = 0;
    for (const auto& loc : tree) {
      assert(loc.name.find("Point_") != std::string::npos);
      ++count;
    }

    assert(count == numElements);
    std::cout << "[OK] testRTreeIterator passed.\n";
  }

}

int main()
{
  std::cout << "--- Starting RTree Tests ---\n";
  vasilenko::testBasicInsertionAndSearch();
  vasilenko::testNodeSplittingAndBalancing();
  vasilenko::testRTreeIterator();
  std::cout << "--- All RTree tests completed successfully! ---\n";
  return 0;
}
