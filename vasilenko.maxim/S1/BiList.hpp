#ifndef BILIST_HPP
#define BILIST_HPP

#include <cstddef>
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

#endif
