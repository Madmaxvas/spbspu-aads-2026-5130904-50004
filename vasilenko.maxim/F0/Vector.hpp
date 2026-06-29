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

void reallocate(std::size_t newCapacity)
    {
      T* newData = static_cast<T*>(::operator new(newCapacity * sizeof(T)));
      std::size_t i = 0;
      try {
        for (; i < size_; ++i) {
          std::construct_at(&newData[i], std::move_if_noexcept(data_[i]));
        }
      } catch (...) {
        for (std::size_t j = 0; j < i; ++j) {
          std::destroy_at(&newData[j]);
        }
        ::operator delete(newData);
        throw;
      }

      for (std::size_t j = 0; j < size_; ++j) {
        std::destroy_at(&data_[j]);
      }
      ::operator delete(data_);

      data_ = newData;
      capacity_ = newCapacity;
    }

  public:
    using iterator = detail::VectorIterator<T>;
    using const_iterator = detail::VectorConstIterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Vector() noexcept : data_(nullptr), size_(0), capacity_(0) {}

    Vector(std::size_t count, const T& value) : data_(nullptr), size_(0), capacity_(0)
    {
      assign(count, value);
    }

    Vector(std::initializer_list<T> init) : data_(nullptr), size_(0), capacity_(0)
    {
      reserve(init.size());
      for (const auto& item : init) {
        push_back(item);
      }
    }

    Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(0)
    {
      T* newData = static_cast<T*>(::operator new(other.size_ * sizeof(T)));
      std::size_t i = 0;
      try {
        for (; i < other.size_; ++i) {
          std::construct_at(&newData[i], other.data_[i]);
        }
      } catch (...) {
        for (std::size_t j = 0; j < i; ++j) {
          std::destroy_at(&newData[j]);
        }
        ::operator delete(newData);
        throw;
      }
      data_ = newData;
      size_ = other.size_;
      capacity_ = other.size_;
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
      ::operator delete(data_);
    }

    void swap(Vector& other) noexcept
    {
      std::swap(data_, other.data_);
      std::swap(size_, other.size_);
      std::swap(capacity_, other.capacity_);
    }

    Vector& operator=(const Vector& other)
    {
      if (this != std::addressof(other)) {
        Vector tmp(other);
        swap(tmp);
      }
      return *this;
    }

    Vector& operator=(Vector&& other) noexcept
    {
      if (this != std::addressof(other)) {
        clear();
        ::operator delete(data_);
        data_ = std::exchange(other.data_, nullptr);
        size_ = std::exchange(other.size_, 0);
        capacity_ = std::exchange(other.capacity_, 0);
      }
      return *this;
    }

    void assign(std::size_t count, const T& value)
    {
      Vector tmp;
      tmp.reserve(count);
      for (std::size_t i = 0; i < count; ++i) {
        tmp.push_back(value);
      }
      swap(tmp);
    }

    template<typename InputIt>
    void assign(InputIt first, InputIt last)
    {
      Vector tmp;
      for (auto it = first; it != last; ++it) {
        tmp.push_back(*it);
      }
      swap(tmp);
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
        std::destroy_at(data_ + size_);
      }
    }

    void reserve(std::size_t newCapacity)
    {
      if (newCapacity > capacity_) {
        reallocate(newCapacity);
      }
    }

    void clear() noexcept
    {
      for (std::size_t i = 0; i < size_; ++i) {
        std::destroy_at(&data_[i]);
      }
      size_ = 0;
    }

    std::size_t size() const noexcept { return size_; }
    std::size_t capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }

    T& operator[](std::size_t index) noexcept { return data_[index]; }
    const T& operator[](std::size_t index) const noexcept { return data_[index]; }

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
