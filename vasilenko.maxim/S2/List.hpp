#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <stdexcept>

namespace vasilenko {

  template < typename T >
  class List
  {
  public:
    List() = default;

    void pushFront(const T & value);
    void pushBack(const T & value);
    void popFront();
    const T & front() const;
    bool empty() const;

  private:
    struct Node
    {
      T data_;
      std::unique_ptr< Node > next_;

      explicit Node(const T & data);
    };

    std::unique_ptr< Node > head_;
    Node * tail_ = nullptr;
  };

  template < typename T >
  List< T >::Node::Node(const T & data):
    data_(data),
    next_(nullptr)
  {}

  template < typename T >
  void List< T >::pushFront(const T & value)
  {
    auto newNode = std::make_unique< Node >(value);
    if (!head_) {
      tail_ = newNode.get();
    }
    newNode->next_ = std::move(head_);
    head_ = std::move(newNode);
  }

  template < typename T >
  void List< T >::pushBack(const T & value)
  {
    auto newNode = std::make_unique< Node >(value);
    Node * rawNode = newNode.get();
    if (!head_) {
      head_ = std::move(newNode);
    } else {
      tail_->next_ = std::move(newNode);
    }
    tail_ = rawNode;
  }

  template < typename T >
  void List< T >::popFront()
  {
    if (empty()) {
      throw std::logic_error("List is empty");
    }
    head = std::move(head_->next_);
    if (!head_) {
      tail_ = nullptr;
    }
  }

  template < typename T >
  const T & List< T >::front() const
  {
    if (empty()) {
      throw std::logic_error("List is empty");
    }
    return head_->data_;
  }

  template < typename T >
  bool List< T >::empty() const
  {
    return head_ == nullptr;
  }

}

#endif
