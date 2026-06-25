#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "List.hpp"

namespace vasilenko {

  template < typename T >
  class Queue
  {
  public:
    Queue() = default;

    void push(const T & rhs);
    void pop();
    const T & front() const;
    bool empty() const;

  private:
    List< T > list_;
  };

  template < typename T >
  void Queue< T >::push(const T & rhs)
  {
    list_.pushBack(rhs);
  }

  template < typename T >
  void Queue< T >::pop()
  {
    list_.popFront();
  }

  template < typename T >
  const T & Queue< T >::front() const
  {
    return list_.front();
  }

  template < typename T >
  bool Queue< T >::empty() const
  {
    return list_.empty();
  }

}

#endif
