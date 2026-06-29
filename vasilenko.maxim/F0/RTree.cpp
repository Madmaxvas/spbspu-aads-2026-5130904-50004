#include "RTree.hpp"

namespace vasilenko {

  namespace {
    vasilenko::detail::RTreeNode* findParentHelper(vasilenko::detail::RTreeNode* current, vasilenko::detail::RTreeNode* child)
    {
      if (current->isLeaf) return nullptr;
      for (std::size_t i = 0; i < current->children.size(); ++i) {
        if (current->children[i].get() == child) return current;
        auto* p = findParentHelper(current->children[i].get(), child);
        if (p) return p;
      }
      return nullptr;
    }
  }

  namespace detail {
    void RTreeIterator::advance()
    {
      while (!nodeStack_.empty()) {
        auto* node = nodeStack_.back();
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
            nodeStack_.push_back(node->children[i - 1].get());
          }
        }
      }
      currentLoc_ = nullptr;
    }

    RTreeIterator::RTreeIterator(RTreeNode* root, bool isEnd)
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
        auto* node = nodeStack_.back();
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
            nodeStack_.push_back(node->children[i - 1].get());
          }
        }
      }
      currentLoc_ = nullptr;
    }

    RTreeConstIterator::RTreeConstIterator(const RTreeNode* root, bool isEnd)
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
    : root_(std::make_unique<detail::RTreeNode>())
  {
  }

  void RTree::updateBoundingBox(detail::RTreeNode* node)
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

  detail::RTreeNode* RTree::chooseLeaf(detail::RTreeNode* node, const Location& loc)
  {
    if (node->isLeaf) {
      return node;
    }
    detail::RTreeNode* bestChild = node->children[0].get();
    long long minEnlargement = -1;

    for (std::size_t i = 0; i < node->children.size(); ++i) {
      detail::BoundingBox tempBox = node->children[i]->box;
      tempBox.expand(loc);
      long long enlargement = tempBox.area() - node->children[i]->box.area();
      if (minEnlargement == -1 || enlargement < minEnlargement) {
        minEnlargement = enlargement;
        bestChild = node->children[i].get();
      }
    }
    return chooseLeaf(bestChild, loc);
  }

  void RTree::splitNode(detail::RTreeNode* node, detail::RTreeNode* parent)
  {
    auto newNode = std::make_unique<detail::RTreeNode>();
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
        newNode->children.push_back(std::move(node->children[i]));
      }
      std::size_t elementsToRemove = node->children.size() - splitIndex;
      for (std::size_t i = 0; i < elementsToRemove; ++i) {
        node->children.pop_back();
      }
    }

    updateBoundingBox(node);
    updateBoundingBox(newNode.get());

    if (parent) {
      parent->children.push_back(std::move(newNode));
      if (parent->children.size() > MAX_ENTRIES) {
        detail::RTreeNode* grandParent = findParentHelper(root_.get(), parent);
        splitNode(parent, grandParent);
      }
    } else {
      auto newRoot = std::make_unique<detail::RTreeNode>();
      newRoot->isLeaf = false;
      newRoot->children.push_back(std::move(root_));
      newRoot->children.push_back(std::move(newNode));
      updateBoundingBox(newRoot.get());
      root_ = std::move(newRoot);
    }
  }

  void RTree::insert(const Location& loc)
  {
    detail::RTreeNode* leaf = chooseLeaf(root_.get(), loc);
    leaf->locations.push_back(loc);

    detail::RTreeNode* curr = leaf;
    while (curr != nullptr) {
      updateBoundingBox(curr);
      curr = findParentHelper(root_.get(), curr);
    }

    if (leaf->locations.size() > MAX_ENTRIES) {
      detail::RTreeNode* parent = findParentHelper(root_.get(), leaf);
      splitNode(leaf, parent);
    }
  }

  Vector<Location*> RTree::findIntersections(int x, int y)
  {
    Vector<Location*> results;
    Vector<detail::RTreeNode*> stack;
    stack.push_back(root_.get());

    while (!stack.empty()) {
      auto* node = stack.back();
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
            stack.push_back(node->children[i].get());
          }
        }
      }
    }
    return results;
  }
}
