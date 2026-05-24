#ifndef BSTREE_ITERATORS_HPP
#define BSTREE_ITERATORS_HPP

#include <iterator>

#include "TreeNode.hpp"

namespace vasilenko {

template<class Key, class Value>
class BSTConstIterator {
public:
  using Node = TreeNode<Key, Value>;
  using iterator_category = std::forward_iterator_tag;
  using value_type = std::pair<const Key, Value>;
  using reference = const value_type&;
  using pointer = const value_type*;

  explicit BSTConstIterator(Node* node):
    current_(node)
  {
  }

  reference operator*() const
  {
    return current_->data_;
  }

  pointer operator->() const
  {
    return &(current_->data_);
  }

  BSTConstIterator& operator++()
  {
    if (current_ == nullptr) {
      return *this;
    }
    if (current_->right_ != nullptr) {
      current_ = current_->right_;
      while (current_->left_ != nullptr) {
        current_ = current_->left_;
      }
    } else {
      Node* p = current_->parent_;
      while (p != nullptr && current_ == p->right_) {
        current_ = p;
        p = p->parent_;
      }
      current_ = p;
    }
    return *this;
  }

  bool operator!=(const BSTConstIterator& other) const
  {
    return current_ != other.current_;
  }

  bool operator==(const BSTConstIterator& other) const
  {
    return current_ == other.current_;
  }

  Node* getNode() const
  {
    return current_;
  }

private:
  Node* current_;
};

}

#endif
