#ifndef VECTOR_ITERATORS_HPP
#define VECTOR_ITERATORS_HPP

#include <cstddef>
#include <iterator>

namespace vasilenko {
  namespace detail {

    template<typename T>
    class VectorIterator {
    public:
      using iterator_category = std::random_access_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = T*;
      using reference = T&;

    private:
      pointer ptr_;

    public:
      explicit VectorIterator(pointer ptr) : ptr_(ptr) {}

      reference operator*() const { return *ptr_; }
      pointer operator->() const { return ptr_; }

      VectorIterator& operator++()
      {
        ++ptr_;
        return *this;
      }

      VectorIterator operator++(int)
      {
        VectorIterator tmp = *this;
        ++(*this);
        return tmp;
      }

      VectorIterator& operator--()
      {
        --ptr_;
        return *this;
      }

      VectorIterator operator--(int)
      {
        VectorIterator tmp = *this;
        --(*this);
        return tmp;
      }

      VectorIterator operator+(difference_type n) const { return VectorIterator(ptr_ + n); }
      VectorIterator operator-(difference_type n) const { return VectorIterator(ptr_ - n); }
      difference_type operator-(const VectorIterator& other) const { return ptr_ - other.ptr_; }

      bool operator==(const VectorIterator& other) const { return ptr_ == other.ptr_; }
      bool operator!=(const VectorIterator& other) const { return ptr_ != other.ptr_; }
      bool operator<(const VectorIterator& other) const { return ptr_ < other.ptr_; }
    };

    template<typename T>
    class VectorConstIterator {
    public:
      using iterator_category = std::random_access_iterator_tag;
      using value_type = const T;
      using difference_type = std::ptrdiff_t;
      using pointer = const T*;
      using reference = const T&;

    private:
      pointer ptr_;

    public:
      explicit VectorConstIterator(pointer ptr) : ptr_(ptr) {}

      reference operator*() const { return *ptr_; }
      pointer operator->() const { return ptr_; }

      VectorConstIterator& operator++()
      {
        ++ptr_;
        return *this;
      }

      VectorConstIterator operator++(int)
      {
        VectorConstIterator tmp = *this;
        ++(*this);
        return tmp;
      }

      VectorConstIterator& operator--()
      {
        --ptr_;
        return *this;
      }

      VectorConstIterator operator--(int)
      {
        VectorConstIterator tmp = *this;
        --(*this);
        return tmp;
      }

      VectorConstIterator operator+(difference_type n) const { return VectorConstIterator(ptr_ + n); }
      VectorConstIterator operator-(difference_type n) const { return VectorConstIterator(ptr_ - n); }
      difference_type operator-(const VectorConstIterator& other) const { return ptr_ - other.ptr_; }

      bool operator==(const VectorConstIterator& other) const { return ptr_ == other.ptr_; }
      bool operator!=(const VectorConstIterator& other) const { return ptr_ != other.ptr_; }
      bool operator<(const VectorConstIterator& other) const { return ptr_ < other.ptr_; }
    };

  }
}

#endif
