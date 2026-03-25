#ifndef COMMON_LIST_HPP
#define COMMON_LIST_HPP

#include <memory>
#include <stdexcept>

namespace vasilenko {

  template <typename T>
  class List {
  public:
    List() = default;

    void pushFront(const T& value)
    {
      auto newNode = std::make_unique<Node>(value);
      if (!head_) {
        tail_ = newNode.get();
      }
      newNode->next_ = std::move(head_);
      head_ = std::move(newNode);
    }

    void pushBack(const T& value)
    {
      auto newNode = std::make_unique<Node>(value);
      Node* rawNode = newNode.get();
      if (!head_) {
        head_ = std::move(newNode);
      } else {
        tail_->next_ = std::move(newNode);
      }
      tail_ = rawNode;
    }

    void popFront()
    {
      if (isEmpty()) {
        throw std::logic_error("List is empty");
      }
      head_ = std::move(head_->next_);
      if (!head_) {
        tail_ = nullptr;
      }
    }

    const T& getFront() const
    {
      if (isEmpty()) {
        throw std::logic_error("List is empty");
      }
      return head_->data_;
    }

    bool isEmpty() const
    {
      return head_ == nullptr;
    }

  private:
    struct Node {
      T data_;
      std::unique_ptr<Node> next_;
      Node(const T& data) : data_(data), next_(nullptr) {}
    };
    std::unique_ptr<Node> head_;
    Node* tail_ = nullptr;
  };

}
#endif
