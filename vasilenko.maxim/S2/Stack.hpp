#ifndef COMMON_STACK_HPP
#define COMMON_STACK_HPP

#include "List.hpp"

namespace vasilenko {

  template <typename T>
  class Stack {
  public:
    Stack() = default;

    void push(const T& rhs)
    {
      list_.pushFront(rhs);
    }

    void pop()
    {
      list_.popFront();
    }

    const T& getTop() const
    {
      return list_.getFront();
    }

    bool isEmpty() const
    {
      return list_.isEmpty();
    }

  private:
    List<T> list_;
  };

}

#endif
