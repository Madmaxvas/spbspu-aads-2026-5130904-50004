#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <iterator>
#include <utility>

namespace vasilenko_maxim {

  template< class T >
  class List;

  namespace detail {

    template< class T >
    struct ListNode {
      T value_;
      ListNode* next_;
      ListNode* prev_;

      ListNode(const T& val, ListNode* next = nullptr, ListNode* prev = nullptr) :
        value_(val),
        next_(next),
        prev_(prev)
      {
      }
    };

  }

  template< class T >
  class LIter {
    friend class List< T >;
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    LIter() :
      node_(nullptr)
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
      node_ = node_->prev_;
      return *this;
    }

    LIter operator--(int)
    {
      LIter tmp = *this;
      node_ = node_->prev_;
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
    explicit LIter(detail::ListNode< T >* node) :
      node_(node)
    {
    }

    detail::ListNode< T >* node_;
  };

  template< class T >
  class LCIter {
    friend class List< T >;
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    LCIter() :
      node_(nullptr)
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
      node_ = node_->prev_;
      return *this;
    }

    LCIter operator--(int)
    {
      LCIter tmp = *this;
      node_ = node_->prev_;
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
    explicit LCIter(const detail::ListNode< T >* node) :
      node_(node)
    {
    }

    const detail::ListNode< T >* node_;
  };

  template< class T >
  class List {
  public:
    using iterator = LIter< T >;
    using const_iterator = LCIter< T >;

    List() :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
    }

    List(const List& other) :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
      try {
        for (auto it = other.cbegin(); it != other.cend(); ++it) {
          pushBack(*it);
        }
      } catch (...) {
        clear();
        throw;
      }
    }

    List(List&& other) noexcept :
      head_(other.head_),
      tail_(other.tail_),
      size_(other.size_)
    {
      other.head_ = nullptr;
      other.tail_ = nullptr;
      other.size_ = 0;
    }

    ~List()
    {
      clear();
    }

    List& operator=(const List& other)
    {
      if (this != &other) {
        List tmp(other);
        std::swap(head_, tmp.head_);
        std::swap(tail_, tmp.tail_);
        std::swap(size_, tmp.size_);
      }
      return *this;
    }

    List& operator=(List&& other) noexcept
    {
      if (this != &other) {
        clear();
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
      }
      return *this;
    }

    void pushBack(const T& value)
    {
      detail::ListNode< T >* newNode = new detail::ListNode< T >(value);
      if (!tail_) {
        head_ = newNode;
        tail_ = newNode;
      } else {
        newNode->prev_ = tail_;
        tail_->next_ = newNode;
        tail_ = newNode;
      }
      size_++;
    }

    void pushFront(const T& value)
    {
      detail::ListNode< T >* newNode = new detail::ListNode< T >(value);
      if (!head_) {
        head_ = newNode;
        tail_ = newNode;
      } else {
        newNode->next_ = head_;
        head_->prev_ = newNode;
        head_ = newNode;
      }
      size_++;
    }

    void popBack() noexcept
    {
      if (!tail_) {
        return;
      }
      detail::ListNode< T >* temp = tail_;
      tail_ = tail_->prev_;
      if (tail_) {
        tail_->next_ = nullptr;
      } else {
        head_ = nullptr;
      }
      delete temp;
      size_--;
    }

    void popFront() noexcept
    {
      if (!head_) {
        return;
      }
      detail::ListNode< T >* temp = head_;
      head_ = head_->next_;
      if (head_) {
        head_->prev_ = nullptr;
      } else {
        tail_ = nullptr;
      }
      delete temp;
      size_--;
    }

    void clear() noexcept
    {
      while (head_) {
        popFront();
      }
    }

    bool empty() const noexcept
    {
      return head_ == nullptr;
    }

    std::size_t size() const noexcept
    {
      return size_;
    }

    iterator begin() noexcept
    {
      return iterator(head_);
    }

    iterator end() noexcept
    {
      return iterator(nullptr);
    }

    const_iterator begin() const noexcept
    {
      return const_iterator(head_);
    }

    const_iterator end() const noexcept
    {
      return const_iterator(nullptr);
    }

    const_iterator cbegin() const noexcept
    {
      return const_iterator(head_);
    }

    const_iterator cend() const noexcept
    {
      return const_iterator(nullptr);
    }

  private:
    detail::ListNode< T >* head_;
    detail::ListNode< T >* tail_;
    std::size_t size_;
  };

}

#endif
