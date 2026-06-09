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

    BiList();
    BiList(const BiList& other);
    BiList(BiList&& other) noexcept;
    ~BiList();

    BiList& operator=(const BiList& other);
    BiList& operator=(BiList&& other) noexcept;

    void pushBack(const T& value);
    void pushFront(const T& value);
    void popBack() noexcept;
    void popFront() noexcept;
    void clear() noexcept;
    bool empty() const noexcept;
    std::size_t size() const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

  private:
    detail::ListNode< T >* head_;
    detail::ListNode< T >* tail_;
    std::size_t size_;
  };
}

template< class T >
vasilenko_maxim::BiList< T >::BiList():
  head_(nullptr),
  tail_(nullptr),
  size_(0)
{}

template< class T >
vasilenko_maxim::BiList< T >::BiList(const BiList& other):
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

template< class T >
vasilenko_maxim::BiList< T >::BiList(BiList&& other) noexcept:
  head_(other.head_),
  tail_(other.tail_),
  size_(other.size_)
{
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template< class T >
vasilenko_maxim::BiList< T >::~BiList()
{
  clear();
}

template< class T >
vasilenko_maxim::BiList< T >& vasilenko_maxim::BiList< T >::operator=(const BiList& other)
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

template< class T >
vasilenko_maxim::BiList< T >& vasilenko_maxim::BiList< T >::operator=(BiList&& other) noexcept
{
  if (this != &other)
  {
    clear();
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }
  return *this;
}

template< class T >
void vasilenko_maxim::BiList< T >::pushBack(const T& value)
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

template< class T >
void vasilenko_maxim::BiList< T >::pushFront(const T& value)
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

template< class T >
void vasilenko_maxim::BiList< T >::popBack() noexcept
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

template< class T >
void vasilenko_maxim::BiList< T >::popFront() noexcept
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

template< class T >
void vasilenko_maxim::BiList< T >::clear() noexcept
{
  while (head_)
  {
    popFront();
  }
}

template< class T >
bool vasilenko_maxim::BiList< T >::empty() const noexcept
{
  return !head_;
}

template< class T >
std::size_t vasilenko_maxim::BiList< T >::size() const noexcept
{
  return size_;
}

template< class T >
typename vasilenko_maxim::BiList< T >::iterator vasilenko_maxim::BiList< T >::begin() noexcept
{
  return iterator(head_, tail_);
}

template< class T >
typename vasilenko_maxim::BiList< T >::iterator vasilenko_maxim::BiList< T >::end() noexcept
{
  return iterator(nullptr, tail_);
}

template< class T >
typename vasilenko_maxim::BiList< T >::const_iterator vasilenko_maxim::BiList< T >::begin() const noexcept
{
  return const_iterator(head_, tail_);
}

template< class T >
typename vasilenko_maxim::BiList< T >::const_iterator vasilenko_maxim::BiList< T >::end() const noexcept
{
  return const_iterator(nullptr, tail_);
}

template< class T >
typename vasilenko_maxim::BiList< T >::const_iterator vasilenko_maxim::BiList< T >::cbegin() const noexcept
{
  return const_iterator(head_, tail_);
}

template< class T >
typename vasilenko_maxim::BiList< T >::const_iterator vasilenko_maxim::BiList< T >::cend() const noexcept
{
  return const_iterator(nullptr, tail_);
}

#endif
