#ifndef VASILENKO_HASHTABLE_ITERATORS_HPP
#define VASILENKO_HASHTABLE_ITERATORS_HPP

#include "slot.hpp"

namespace vasilenko {

template< class Key, class Value >
class HashTableIterator {
public:
  using Node = HashNode< Key, Value >;

  HashTableIterator(Node *ptr, Node *end) : ptr_(ptr), end_(end) {
    advanceToOccupied();
  }

  Node& operator*() { return *ptr_; }
  Node* operator->() { return ptr_; }

  HashTableIterator& operator++() {
    ++ptr_;
    advanceToOccupied();
    return *this;
  }

  bool operator!=(const HashTableIterator &other) const { return ptr_ != other.ptr_; }
  bool operator==(const HashTableIterator &other) const { return ptr_ == other.ptr_; }

private:
  Node *ptr_;
  Node *end_;

  void advanceToOccupied() {
    while (ptr_ != end_ && ptr_->state_ != SlotState::Occupied) {
      ++ptr_;
    }
  }
};

}

#endif
