#ifndef BILIST_HPP
#define BILIST_HPP

#include <cstddef>
#include <utility>
#include "ListNode.hpp"
#include "LIter.hpp"
#include "LCIter.hpp"

namespace vasilenko_maxim
{
  template< class T >
  class BiList
  {
  public:
    using iterator = LIter< T >;
    using const_iterator = LCIter< T >;

    BiList():
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
    }

    BiList(const BiList& other):
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
      try
      {
        for (auto it = other.cbegin(); it != other.cend(); ++it)
        {
          pushBack(*it);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    BiList(BiList&& other) noexcept:
      head_(other.head_),
      tail_(other.tail_),
      size_(other.size_)
    {
      other.head_ = nullptr;
      other.tail_ = nullptr;
      other.size_ = 0;
    }

    ~BiList()
    {
      clear();
    }

    BiList& operator=(const BiList& other)
    {
      if (this != &other)
      {
        BiList tmp(other);
        std::swap(head_, tmp.head_);
        std::swap(tail_, tmp.tail_);
        std::swap(size_, tmp.size_);
      }
      return *this;
    }

    BiList& operator=(BiList&& other) noexcept
    {
      if (this != &other)
      {
        clear();
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
      }
      return *this;
    }

    void pushBack(const T& value)
    {
      detail::ListNode< T >* newNode = new detail::ListNode< T >(value, nullptr, tail_);
      if (tail_)
      {
        tail_->next_ = newNode;
      }
      else
      {
        head_ = newNode;
      }
      tail_ = newNode;
      size_++;
    }

    void pushFront(const T& value)
    {
      detail::ListNode< T >* newNode = new detail::ListNode< T >(value, head_, nullptr);
      if (head_)
      {
        head_->prev_ = newNode;
      }
      else
      {
        tail_ = newNode;
      }
      head_ = newNode;
      size_++;
    }

    void popBack() noexcept
    {
      if (!tail_)
      {
        return;
      }
      detail::ListNode< T >* temp = tail_;
      tail_ = tail_->prev_;
      if (tail_)
      {
        tail_->next_ = nullptr;
      }
      else
      {
        head_ = nullptr;
      }
      delete temp;
      size_--;
    }

    void popFront() noexcept
    {
      if (!head_)
      {
        return;
      }
      detail::ListNode< T >* temp = head_;
      head_ = head_->next_;
      if (head_)
      {
        head_->prev_ = nullptr;
      }
      else
      {
        tail_ = nullptr;
      }
      delete temp;
      size_--;
    }

    void clear() noexcept
    {
      while (head_)
      {
        popFront();
      }
    }

    bool empty() const noexcept
    {
      return !head_;
    }

    std::size_t size() const noexcept
    {
      return size_;
    }

    iterator begin() noexcept
    {
      return iterator(head_, tail_);
    }

    iterator end() noexcept
    {
      return iterator(nullptr, tail_);
    }

    const_iterator begin() const noexcept
    {
      return const_iterator(head_, tail_);
    }

    const_iterator end() const noexcept
    {
      return const_iterator(nullptr, tail_);
    }

    const_iterator cbegin() const noexcept
    {
      return const_iterator(head_, tail_);
    }

    const_iterator cend() const noexcept
    {
      return const_iterator(nullptr, tail_);
    }

  private:
    detail::ListNode< T >* head_;
    detail::ListNode< T >* tail_;
    std::size_t size_;
  };
}

#endif
