#include <catch2/catch.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "BSTree.hpp"

TEST_CASE("BSTree: Basic Push, Get, and Iteration", "[bstree]")
{
  vasilenko::BSTree<int, std::string> tree;
  tree.push(5, "five");
  tree.push(3, "three");
  tree.push(7, "seven");

  REQUIRE(tree.get(5) == "five");
  REQUIRE(tree.get(3) == "three");
  REQUIRE(tree.get(7) == "seven");

  tree.push(5, "FIVE");
  REQUIRE(tree.get(5) == "FIVE");

  REQUIRE_THROWS_AS(tree.get(10), std::out_of_range);

  std::vector<int> expected = {3, 5, 7};
  std::vector<int> actual;
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    actual.push_back(it->first);
  }
  REQUIRE(actual == expected);
}

TEST_CASE("BSTree: Removal Maintains Reference Stability", "[bstree]")
{
  vasilenko::BSTree<int, std::string> tree;
  tree.push(10, "ten");
  tree.push(5, "five");
  tree.push(15, "fifteen");

  auto it = tree.begin();
  REQUIRE(it->first == 5);

  std::string dropped = tree.drop(15);
  REQUIRE(dropped == "fifteen");
  REQUIRE(it->first == 5);
  REQUIRE_THROWS_AS(tree.get(15), std::out_of_range);
}

TEST_CASE("BSTree: Rotations Change Structure Correctly", "[bstree]")
{
  SECTION("Left Rotation")
  {
    vasilenko::BSTree<int, std::string> tree;
    tree.push(1, "A");
    tree.push(2, "B");
    tree.push(3, "C");

    REQUIRE(tree.height() == 3);
    auto rootIt = tree.begin();
    auto newRootIt = tree.rotateLeft(rootIt);

    REQUIRE(newRootIt->first == 2);
    REQUIRE(tree.height() == 2);
  }

  SECTION("Right Rotation")
  {
    vasilenko::BSTree<int, std::string> tree;
    tree.push(3, "C");
    tree.push(2, "B");
    tree.push(1, "A");

    REQUIRE(tree.height() == 3);
    auto it = tree.begin();
    ++it;
    ++it;
    auto newRootIt = tree.rotateRight(it);

    REQUIRE(newRootIt->first == 2);
    REQUIRE(tree.height() == 2);
  }
}
