#ifndef VASILENKO_VECTOR_ITERATORS_HPP
#define VASILENKO_VECTOR_ITERATORS_HPP

namespace vasilenko {

template< class T >
class VectorIterator {
public:
  using pointer = T*;
  using reference = T&;

  VectorIterator(pointer ptr) : ptr_(ptr) {}
  reference operator*() const { return *ptr_; }
  VectorIterator& operator++() { ++ptr_; return *this; }
  bool operator!=(const VectorIterator &other) const { return ptr_ != other.ptr_; }
  bool operator==(const VectorIterator &other) const { return ptr_ == other.ptr_; }
private:
  pointer ptr_;
};

template< class T >
class VectorConstIterator {
public:
  using pointer = const T*;
  using reference = const T&;

  VectorConstIterator(pointer ptr) : ptr_(ptr) {}
  reference operator*() const { return *ptr_; }
  VectorConstIterator& operator++() { ++ptr_; return *this; }
  bool operator!=(const VectorConstIterator &other) const { return ptr_ != other.ptr_; }
  bool operator==(const VectorConstIterator &other) const { return ptr_ == other.ptr_; }
private:
  pointer ptr_;
};

}

#endif
