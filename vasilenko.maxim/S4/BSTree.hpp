#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <functional>
#include <stdexcept>
#include <utility>

#include "TreeNode.hpp"
#include "BSTree-iterators.hpp"
#include "tree-traverse.hpp"

namespace vasilenko {

template<class Key, class Value, class Compare = std::less<Key>>
class BSTree {
public:
  using Node = TreeNode<Key, Value>;
  using const_iterator = BSTConstIterator<Key, Value>;

  BSTree():
    root_(nullptr),
    comp_(),
    size_(0)
  {
  }

  ~BSTree()
  {
    clearTree(root_);
  }

  BSTree(const BSTree&) = delete;
  BSTree& operator=(const BSTree&) = delete;

  BSTree(BSTree&& other) noexcept:
    root_(other.root_),
    comp_(other.comp_),
    size_(other.size_)
  {
    other.root_ = nullptr;
    other.size_ = 0;
  }

  BSTree& operator=(BSTree&& other) noexcept
  {
    if (this != &other) {
      clearTree(root_);
      root_ = other.root_;
      size_ = other.size_;
      other.root_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  void push(const Key& k, const Value& v)
  {
    if (root_ == nullptr) {
      root_ = new Node(k, v);
      size_++;
      return;
    }
    Node* current = root_;
    Node* parent = nullptr;
    while (current != nullptr) {
      parent = current;
      if (comp_(k, current->data_.first)) {
        current = current->left_;
      } else if (comp_(current->data_.first, k)) {
        current = current->right_;
      } else {
        current->data_.second = v;
        return;
      }
    }
    if (comp_(k, parent->data_.first)) {
      parent->left_ = new Node(k, v, parent);
    } else {
      parent->right_ = new Node(k, v, parent);
    }
    size_++;
  }

  Value get(const Key& k) const
  {
    Node* current = root_;
    while (current != nullptr) {
      if (comp_(k, current->data_.first)) {
        current = current->left_;
      } else if (comp_(current->data_.first, k)) {
        current = current->right_;
      } else {
        return current->data_.second;
      }
    }
    throw std::out_of_range("Key not found");
  }

  Value drop(const Key& k)
  {
    Node* current = root_;
    while (current != nullptr) {
      if (comp_(k, current->data_.first)) {
        current = current->left_;
      } else if (comp_(current->data_.first, k)) {
        current = current->right_;
      } else {
        Value val = current->data_.second;
        removeNode(current);
        size_--;
        return val;
      }
    }
    throw std::out_of_range("Key not found");
  }

  const_iterator begin() const
  {
    Node* current = root_;
    if (current != nullptr) {
      while (current->left_ != nullptr) {
        current = current->left_;
      }
    }
    return const_iterator(current);
  }

  const_iterator end() const
  {
    return const_iterator(nullptr);
  }

  const_iterator rotateLeft(const_iterator it)
  {
    Node* a = it.getNode();
    if (a == nullptr || a->right_ == nullptr) {
      return it;
    }
    Node* b = a->right_;
    a->right_ = b->left_;
    if (b->left_ != nullptr) {
      b->left_->parent_ = a;
    }
    b->parent_ = a->parent_;
    if (a->parent_ == nullptr) {
      root_ = b;
    } else if (a == a->parent_->left_) {
      a->parent_->left_ = b;
    } else {
      a->parent_->right_ = b;
    }
    b->left_ = a;
    a->parent_ = b;
    return const_iterator(b);
  }

  const_iterator rotateRight(const_iterator it)
  {
    Node* a = it.getNode();
    if (a == nullptr || a->left_ == nullptr) {
      return it;
    }
    Node* b = a->left_;
    a->left_ = b->right_;
    if (b->right_ != nullptr) {
      b->right_->parent_ = a;
    }
    b->parent_ = a->parent_;
    if (a->parent_ == nullptr) {
      root_ = b;
    } else if (a == a->parent_->right_) {
      a->parent_->right_ = b;
    } else {
      a->parent_->left_ = b;
    }
    b->right_ = a;
    a->parent_ = b;
    return const_iterator(b);
  }

  const_iterator rotateLargeLeft(const_iterator it)
  {
    Node* node = it.getNode();
    if (node != nullptr && node->right_ != nullptr) {
      rotateRight(const_iterator(node->right_));
      return rotateLeft(it);
    }
    return it;
  }

  const_iterator rotateLargeRight(const_iterator it)
  {
    Node* node = it.getNode();
    if (node != nullptr && node->left_ != nullptr) {
      rotateLeft(const_iterator(node->left_));
      return rotateRight(it);
    }
    return it;
  }

  std::size_t height(const_iterator it) const
  {
    return calculateHeight(it.getNode());
  }

  std::size_t height() const
  {
    return calculateHeight(root_);
  }

private:
  Node* root_;
  Compare comp_;
  std::size_t size_;

  void removeNode(Node* node)
  {
    if (node->left_ == nullptr && node->right_ == nullptr) {
      if (node->parent_ == nullptr) {
        root_ = nullptr;
      } else if (node == node->parent_->left_) {
        node->parent_->left_ = nullptr;
      } else {
        node->parent_->right_ = nullptr;
      }
      delete node;
    } else if (node->left_ != nullptr && node->right_ == nullptr) {
      if (node->parent_ == nullptr) {
        root_ = node->left_;
        root_->parent_ = nullptr;
      } else if (node == node->parent_->left_) {
        node->parent_->left_ = node->left_;
        node->left_->parent_ = node->parent_;
      } else {
        node->parent_->right_ = node->left_;
        node->left_->parent_ = node->parent_;
      }
      delete node;
    } else if (node->left_ == nullptr && node->right_ != nullptr) {
      if (node->parent_ == nullptr) {
        root_ = node->right_;
        root_->parent_ = nullptr;
      } else if (node == node->parent_->left_) {
        node->parent_->left_ = node->right_;
        node->right_->parent_ = node->parent_;
      } else {
        node->parent_->right_ = node->right_;
        node->right_->parent_ = node->parent_;
      }
      delete node;
    } else {
      Node* successor = node->right_;
      while (successor->left_ != nullptr) {
        successor = successor->left_;
      }
      if (successor->parent_ != node) {
        successor->parent_->left_ = successor->right_;
        if (successor->right_ != nullptr) {
          successor->right_->parent_ = successor->parent_;
        }
        successor->right_ = node->right_;
        successor->right_->parent_ = successor;
      }
      if (node->parent_ == nullptr) {
        root_ = successor;
      } else if (node == node->parent_->left_) {
        node->parent_->left_ = successor;
      } else {
        node->parent_->right_ = successor;
      }
      successor->parent_ = node->parent_;
      successor->left_ = node->left_;
      successor->left_->parent_ = successor;
      delete node;
    }
  }
};

}

#endif
