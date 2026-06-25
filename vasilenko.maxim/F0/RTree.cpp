#include "RTree.hpp"

namespace vasilenko {
  namespace detail {

    void RTreeIterator::advance()
    {
      while (!nodeStack_.empty()) {
        auto node = nodeStack_.back();
        if (node->isLeaf) {
          if (locIndex_ < node->locations.size()) {
            currentLoc_ = &node->locations[locIndex_];
            return;
          } else {
            nodeStack_.pop_back();
            locIndex_ = 0;
          }
        } else {
          nodeStack_.pop_back();
          for (std::size_t i = node->children.size(); i > 0; --i) {
            nodeStack_.push_back(node->children[i - 1]);
          }
        }
      }
      currentLoc_ = nullptr;
    }

    RTreeIterator::RTreeIterator(std::shared_ptr<RTreeNode> root, bool isEnd)
      : locIndex_(0), currentLoc_(nullptr)
    {
      if (!isEnd && root) {
        nodeStack_.push_back(root);
        advance();
      }
    }

    RTreeIterator& RTreeIterator::operator++()
    {
      ++locIndex_;
      advance();
      return *this;
    }

    RTreeIterator RTreeIterator::operator++(int)
    {
      RTreeIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    void RTreeConstIterator::advance()
    {
      while (!nodeStack_.empty()) {
        auto node = nodeStack_.back();
        if (node->isLeaf) {
          if (locIndex_ < node->locations.size()) {
            currentLoc_ = &node->locations[locIndex_];
            return;
          } else {
            nodeStack_.pop_back();
            locIndex_ = 0;
          }
        } else {
          nodeStack_.pop_back();
          for (std::size_t i = node->children.size(); i > 0; --i) {
            nodeStack_.push_back(node->children[i - 1]);
          }
        }
      }
      currentLoc_ = nullptr;
    }

    RTreeConstIterator::RTreeConstIterator(std::shared_ptr<RTreeNode> root, bool isEnd)
      : locIndex_(0), currentLoc_(nullptr)
    {
      if (!isEnd && root) {
        nodeStack_.push_back(root);
        advance();
      }
    }

    RTreeConstIterator& RTreeConstIterator::operator++()
    {
      ++locIndex_;
      advance();
      return *this;
    }

    RTreeConstIterator RTreeConstIterator::operator++(int)
    {
      RTreeConstIterator tmp = *this;
      ++(*this);
      return tmp;
    }

  }

  RTree::RTree()
  {
    root_ = std::make_shared<detail::RTreeNode>();
  }

  void RTree::updateBoundingBox(std::shared_ptr<detail::RTreeNode> node)
  {
    if (node->isLeaf) {
      if (!node->locations.empty()) {
        node->box = { node->locations[0].minX, node->locations[0].minY,
                      node->locations[0].maxX, node->locations[0].maxY };
        for (std::size_t i = 1; i < node->locations.size(); ++i) {
          node->box.expand(node->locations[i]);
        }
      }
    } else {
      if (!node->children.empty()) {
        node->box = node->children[0]->box;
        for (std::size_t i = 1; i < node->children.size(); ++i) {
          node->box.expand(node->children[i]->box);
        }
      }
    }
  }

  std::shared_ptr<detail::RTreeNode> RTree::chooseLeaf(std::shared_ptr<detail::RTreeNode> node, const Location& loc)
  {
    if (node->isLeaf) {
      return node;
    }

    std::shared_ptr<detail::RTreeNode> bestChild = node->children[0];
    long long minEnlargement = -1;

    for (std::size_t i = 0; i < node->children.size(); ++i) {
      detail::BoundingBox tempBox = node->children[i]->box;
      tempBox.expand(loc);
      long long enlargement = tempBox.area() - node->children[i]->box.area();

      if (minEnlargement == -1 || enlargement < minEnlargement) {
        minEnlargement = enlargement;
        bestChild = node->children[i];
      }
    }
    return chooseLeaf(bestChild, loc);
  }

  void RTree::splitNode(std::shared_ptr<detail::RTreeNode> node, std::shared_ptr<detail::RTreeNode> parent)
  {
    auto newNode = std::make_shared<detail::RTreeNode>();
    newNode->isLeaf = node->isLeaf;

    std::size_t splitIndex = node->isLeaf ? node->locations.size() / 2 : node->children.size() / 2;

    if (node->isLeaf) {
      for (std::size_t i = splitIndex; i < node->locations.size(); ++i) {
        newNode->locations.push_back(node->locations[i]);
      }
      std::size_t elementsToRemove = node->locations.size() - splitIndex;
      for (std::size_t i = 0; i < elementsToRemove; ++i) {
        node->locations.pop_back();
      }
    } else {
      for (std::size_t i = splitIndex; i < node->children.size(); ++i) {
        newNode->children.push_back(node->children[i]);
      }
      std::size_t elementsToRemove = node->children.size() - splitIndex;
      for (std::size_t i = 0; i < elementsToRemove; ++i) {
        node->children.pop_back();
      }
    }

    updateBoundingBox(node);
    updateBoundingBox(newNode);

    if (parent) {
      parent->children.push_back(newNode);
    } else {
      auto newRoot = std::make_shared<detail::RTreeNode>();
      newRoot->isLeaf = false;
      newRoot->children.push_back(node);
      newRoot->children.push_back(newNode);
      updateBoundingBox(newRoot);
      root_ = newRoot;
    }
  }

  void RTree::insert(const Location& loc)
  {
    std::shared_ptr<detail::RTreeNode> leaf = chooseLeaf(root_, loc);
    leaf->locations.push_back(loc);
    updateBoundingBox(leaf);

    if (leaf->locations.size() > MAX_ENTRIES) {
      splitNode(leaf, nullptr);
    }
  }

  Vector<Location*> RTree::findIntersections(int x, int y)
  {
    Vector<Location*> results;
    Vector<std::shared_ptr<detail::RTreeNode>> stack;
    stack.push_back(root_);

    while (!stack.empty()) {
      auto node = stack.back();
      stack.pop_back();

      if (node->box.contains(x, y)) {
        if (node->isLeaf) {
          for (std::size_t i = 0; i < node->locations.size(); ++i) {
            if (x >= node->locations[i].minX && x <= node->locations[i].maxX &&
                y >= node->locations[i].minY && y <= node->locations[i].maxY) {
              results.push_back(&node->locations[i]);
            }
          }
        } else {
          for (std::size_t i = 0; i < node->children.size(); ++i) {
            stack.push_back(node->children[i]);
          }
        }
      }
    }
    return results;
  }

}
