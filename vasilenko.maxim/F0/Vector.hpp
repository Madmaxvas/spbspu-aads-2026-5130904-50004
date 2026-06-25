#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Vector_Iterators.hpp"
#include <algorithm>
#include <initializer_list>
#include <memory>
#include <utility>

namespace vasilenko {

  template<typename T>
  class Vector {
  private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;
    std::allocator<T> alloc_;

    void reallocate(std::size_t newCapacity)
    {
      T* newData = alloc_.allocate(newCapacity);
      std::size_t i = 0;
      try {
        for (; i < size_; ++i) {
          std::construct_at(&newData[i], std::move_if_noexcept(data_[i]));
        }
      } catch (...) {
        for (std::size_t j = 0; j < i; ++j) {
          std::destroy_at(&newData[j]);
        }
        alloc_.deallocate(newData, newCapacity);
        throw;
      }

      for (std::size_t j = 0; j < size_; ++j) {
        std::destroy_at(&data_[j]);
      }
      alloc_.deallocate(data_, capacity_);

      data_ = newData;
      capacity_ = newCapacity;
    }

  public:
    using iterator = detail::VectorIterator<T>;
    using const_iterator = detail::VectorConstIterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    Vector(std::size_t count, const T& value) : data_(nullptr), size_(0), capacity_(0)
    {
      assign(count, value);
    }

    Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(0)
    {
      reserve(other.size_);
      for (std::size_t i = 0; i < other.size_; ++i) {
        push_back(other.data_[i]);
      }
    }

    Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
    {
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }

    ~Vector()
    {
      clear();
      alloc_.deallocate(data_, capacity_);
    }

    Vector& operator=(const Vector& other)
    {
      if (this != &other) {
        Vector tmp(other);
        std::swap(data_, tmp.data_);
        std::swap(size_, tmp.size_);
        std::swap(capacity_, tmp.capacity_);
      }
      return *this;
    }

    Vector& operator=(Vector&& other) noexcept
    {
      if (this != &other) {
        clear();
        alloc_.deallocate(data_, capacity_);
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
      }
      return *this;
    }

    void assign(std::size_t count, const T& value)
    {
      clear();
      reserve(count);
      for (std::size_t i = 0; i < count; ++i) {
        std::construct_at(&data_[i], value);
      }
      size_ = count;
    }

    template<typename InputIt>
    void assign(InputIt first, InputIt last)
    {
      clear();
      for (auto it = first; it != last; ++it) {
        push_back(*it);
      }
    }

    void push_back(const T& value)
    {
      if (size_ == capacity_) {
        reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
      }
      std::construct_at(&data_[size_], value);
      ++size_;
    }

    void push_back(T&& value)
    {
      if (size_ == capacity_) {
        reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
      }
      std::construct_at(&data_[size_], std::move(value));
      ++size_;
    }

    void pop_back()
    {
      if (size_ > 0) {
        --size_;
        std::destroy_at(&data_[size_]);
      }
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      std::size_t startIndex = first - cbegin();
      std::size_t count = last - first;

      for (std::size_t i = startIndex; i < size_ - count; ++i) {
        data_[i] = std::move(data_[i + count]);
      }
      for (std::size_t i = size_ - count; i < size_; ++i) {
        std::destroy_at(&data_[i]);
      }
      size_ -= count;
      return begin() + startIndex;
    }

    void reserve(std::size_t newCapacity)
    {
      if (newCapacity > capacity_) {
        reallocate(newCapacity);
      }
    }

    void clear()
    {
      for (std::size_t i = 0; i < size_; ++i) {
        std::destroy_at(&data_[i]);
      }
      size_ = 0;
    }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    T& operator[](std::size_t index) { return data_[index]; }
    const T& operator[](std::size_t index) const { return data_[index]; }

    T& back() { return data_[size_ - 1]; }
    const T& back() const { return data_[size_ - 1]; }

    iterator begin() { return iterator(data_); }
    iterator end() { return iterator(data_ + size_); }
    const_iterator begin() const { return const_iterator(data_); }
    const_iterator end() const { return const_iterator(data_ + size_); }
    const_iterator cbegin() const { return const_iterator(data_); }
    const_iterator cend() const { return const_iterator(data_ + size_); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
  };

}

#endif
