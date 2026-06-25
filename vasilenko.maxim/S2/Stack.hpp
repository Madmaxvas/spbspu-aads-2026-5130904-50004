#ifndef STACK_HPP
#define STACK_HPP

#include "List.hpp"

namespace vasilenko {

  template < typename T >
  class Stack
  {
  public:
    Stack() = default;

    void push(const T & rhs);
    void pop();
    const T & top() const;
    bool empty() const;

  private:
    List< T > list_;
  };

  template < typename T >
  void Stack< T >::push(const T & rhs)
  {
    list_.pushFront(rhs);
  }

  template < typename T >
  void Stack< T >::pop()
  {
    list_.popFront();
  }

  template < typename T >
  const T & Stack< T >::top() const
  {
    return list_.front();
  }

  template < typename T >
  bool Stack< T >::empty() const
  {
    return list_.empty();
  }

}

#endif
