#ifndef COMMON_STACK_HPP
#define COMMON_STACK_HPP
#include "List.hpp"
namespace vasilenko {
  template <typename T>
  class Stack {
  public:
    void push(const T& rhs) { list_.pushFront(rhs); }
    void pop() { list_.popFront(); }
    const T& getTop() const { return list_.getFront(); }
    bool isEmpty() const { return list_.isEmpty(); }
  private:
    List<T> list_;
  };
}
#endif

#ifndef COMMON_QUEUE_HPP
#define COMMON_QUEUE_HPP
#include "List.hpp"
namespace vasilenko {
  template <typename T>
  class Queue {
  public:
    void push(const T& rhs) { list_.pushBack(rhs); }
    void pop() { list_.popFront(); }
    const T& getFront() const { return list_.getFront(); }
    bool isEmpty() const { return list_.isEmpty(); }
  private:
    List<T> list_;
  };
}
#endif
