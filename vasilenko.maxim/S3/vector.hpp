#ifndef VASILENKO_VECTOR_HPP
#define VASILENKO_VECTOR_HPP

#include "vector-iterators.hpp"
#include <utility>
#include <cstddef>

namespace vasilenko {

template< class T >
class Vector {
public:
  using iterator = VectorIterator< T >;
  using const_iterator = VectorConstIterator< T >;

  Vector() : size_(0), capacity_(0), data_(nullptr) {}

  Vector(std::size_t cap) : size_(cap), capacity_(cap) {
    data_ = new T[capacity_];
  }

  ~Vector() { delete[] data_; }

  Vector(const Vector &other) : size_(other.size_), capacity_(other.capacity_) {
    data_ = new T[capacity_];
    for (std::size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }

  Vector& operator=(Vector other) {
    swap(other);
    return *this;
  }

  void push_back(const T &val) {
    if (size_ == capacity_) {
      std::size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
      T *new_data = new T[new_cap];
      for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
      }
      delete[] data_;
      data_ = new_data;
      capacity_ = new_cap;
    }
    data_[size_++] = val;
  }

  T& operator[](std::size_t idx) { return data_[idx]; }
  const T& operator[](std::size_t idx) const { return data_[idx]; }

  std::size_t size() const { return size_; }

  iterator begin() { return iterator(data_); }
  iterator end() { return iterator(data_ + size_); }

  const_iterator begin() const { return const_iterator(data_); }
  const_iterator end() const { return const_iterator(data_ + size_); }

  void swap(Vector &other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

private:
  std::size_t size_;
  std::size_t capacity_;
  T *data_;
};

}

#endif
