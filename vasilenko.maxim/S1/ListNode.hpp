#ifndef LISTNODE_HPP
#define LISTNODE_HPP

namespace vasilenko_maxim
{
  namespace detail
  {
    template< class T >
    struct ListNode
    {
      T value_;
      ListNode* next_;
      ListNode* prev_;

      ListNode(const T& val, ListNode* next = nullptr, ListNode* prev = nullptr):
        value_(val),
        next_(next),
        prev_(prev)
      {
      }
    };
  }
}

#endif
