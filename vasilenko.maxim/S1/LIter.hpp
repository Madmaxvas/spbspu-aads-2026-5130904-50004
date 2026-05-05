#ifndef LITER_HPP
#define LITER_HPP

#include <iterator>
#include "ListNode.hpp"

namespace vasilenko_maxim
{
  template< class T >
  class BiList;

  template< class T >
  class LIter
  {
    friend class BiList< T >;
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    LIter():
      node_(nullptr),
      tail_(nullptr)
    {
    }

    reference operator*() const
    {
      return node_->value_;
    }

    pointer operator->() const
    {
      return &(node_->value_);
    }

    LIter& operator++()
    {
      node_ = node_->next_;
      return *this;
    }

    LIter operator++(int)
    {
      LIter tmp = *this;
      node_ = node_->next_;
      return tmp;
    }

    LIter& operator--()
    {
      node_ = node_ ? node_->prev_ : tail_;
      return *this;
    }

    LIter operator--(int)
    {
      LIter tmp = *this;
      node_ = node_ ? node_->prev_ : tail_;
      return tmp;
    }

    bool operator==(const LIter& other) const
    {
      return node_ == other.node_;
    }

    bool operator!=(const LIter& other) const
    {
      return node_ != other.node_;
    }

  private:
    LIter(detail::ListNode< T >* node, detail::ListNode< T >* tail):
      node_(node),
      tail_(tail)
    {
    }

    detail::ListNode< T >* node_;
    detail::ListNode< T >* tail_;
  };
}

#endif
