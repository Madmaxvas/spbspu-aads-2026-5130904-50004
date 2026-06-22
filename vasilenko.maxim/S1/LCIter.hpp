#ifndef LCITER_HPP
#define LCITER_HPP

#include <iterator>
#include <cstddef>
#include "ListNode.hpp"

namespace vasilenko
{
  template< class T >
  class BiList;

  template< class T >
  class LCIter
  {
    friend class BiList< T >;
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    LCIter():
      node_(nullptr),
      tail_(nullptr)
    {}

    reference operator*() const
    {
      return node_->value_;
    }

    pointer operator->() const
    {
      return &(node_->value_);
    }

    LCIter& operator++()
    {
      node_ = node_->next_;
      return *this;
    }

    LCIter operator++(int)
    {
      LCIter tmp = *this;
      node_ = node_->next_;
      return tmp;
    }

    LCIter& operator--()
    {
      node_ = node_ ? node_->prev_ : tail_;
      return *this;
    }

    LCIter operator--(int)
    {
      LCIter tmp = *this;
      node_ = node_ ? node_->prev_ : tail_;
      return tmp;
    }

    bool operator==(const LCIter& other) const
    {
      return node_ == other.node_;
    }

    bool operator!=(const LCIter& other) const
    {
      return node_ != other.node_;
    }

  private:
    LCIter(const ListNode< T >* node, const ListNode< T >* tail):
      node_(node),
      tail_(tail)
    {}

    const ListNode< T >* node_;
    const ListNode< T >* tail_;
  };
}

#endif
