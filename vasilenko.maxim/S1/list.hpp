#ifndef VASILENKO_MAXIM_LIST_HPP
#define VASILENKO_MAXIM_LIST_HPP

#include <utility>

namespace vasilenko_maxim {
  template< class T >
  class LIter;

  template< class T >
  class LCIter;

  template< class T >
  class List {
  public:
    using value_type = T;

    List();
    List(const List& other);
    List(List&& other) noexcept;
    ~List();

    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;

    void pushBack(const T& value);
    void pushFront(const T& value);
    void popBack();
    void popFront();
    void clear();
    bool isEmpty() const;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    LIter< T > begin();
    LIter< T > end();
    LCIter< T > begin() const;
    LCIter< T > end() const;

  private:
    struct Node {
      T data_;
      Node* prev_;
      Node* next_;

      Node(const T& data, Node* prev, Node* next);
    };

    Node* head_;
    Node* tail_;

    friend class LIter< T >;
    friend class LCIter< T >;
  };

  template< class T >
  class LIter {
  public:
    LIter(typename List< T >::Node* node);

    T& operator*();
    T* operator->();
    LIter& operator++();
    bool operator==(const LIter& other) const;
    bool operator!=(const LIter& other) const;

  private:
    typename List< T >::Node* node_;
  };

  template< class T >
  class LCIter {
  public:
    LCIter(const typename List< T >::Node* node);

    const T& operator*() const;
    const T* operator->() const;
    LCIter& operator++();
    bool operator==(const LCIter& other) const;
    bool operator!=(const LCIter& other) const;

  private:
    const typename List< T >::Node* node_;
  };

  template< class T >
  List< T >::Node::Node(const T& data, Node* prev, Node* next):
    data_(data),
    prev_(prev),
    next_(next)
  {}

  template< class T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr)
  {}

  template< class T >
  List< T >::List(const List& other):
    head_(nullptr),
    tail_(nullptr)
  {
    for (LCIter< T > it = other.begin(); it != other.end(); ++it) {
      pushBack(*it);
    }
  }

  template< class T >
  List< T >::List(List&& other) noexcept:
    head_(other.head_),
    tail_(other.tail_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template< class T >
  List< T >& List< T >::operator=(const List& other)
  {
    if (this != &other) {
      List< T > temp(other);
      std::swap(head_, temp.head_);
      std::swap(tail_, temp.tail_);
    }
    return *this;
  }

  template< class T >
  List< T >& List< T >::operator=(List&& other) noexcept
  {
    if (this != &other) {
      clear();
      head_ = other.head_;
      tail_ = other.tail_;
      other.head_ = nullptr;
      other.tail_ = nullptr;
    }
    return *this;
  }

  template< class T >
  void List< T >::pushBack(const T& value)
  {
    Node* newNode = new Node(value, tail_, nullptr);
    if (tail_) {
      tail_->next_ = newNode;
    } else {
      head_ = newNode;
    }
    tail_ = newNode;
  }

  template< class T >
  void List< T >::pushFront(const T& value)
  {
    Node* newNode = new Node(value, nullptr, head_);
    if (head_) {
      head_->prev_ = newNode;
    } else {
      tail_ = newNode;
    }
    head_ = newNode;
  }

  template< class T >
  void List< T >::popFront()
  {
    if (head_) {
      Node* temp = head_;
      head_ = head_->next_;
      if (head_) {
        head_->prev_ = nullptr;
      } else {
        tail_ = nullptr;
      }
      delete temp;
    }
  }

  template< class T >
  void List< T >::popBack()
  {
    if (tail_) {
      Node* temp = tail_;
      tail_ = tail_->prev_;
      if (tail_) {
        tail_->next_ = nullptr;
      } else {
        head_ = nullptr;
      }
      delete temp;
    }
  }

  template< class T >
  void List< T >::clear()
  {
    while (!isEmpty()) {
      popFront();
    }
  }

  template< class T >
  bool List< T >::isEmpty() const
  {
    return head_ == nullptr;
  }

  template< class T >
  T& List< T >::front() { return head_->data_; }

  template< class T >
  const T& List< T >::front() const { return head_->data_; }

  template< class T >
  T& List< T >::back() { return tail_->data_; }

  template< class T >
  const T& List< T >::back() const { return tail_->data_; }

  template< class T >
  LIter< T > List< T >::begin() { return LIter< T >(head_); }

  template< class T >
  LIter< T > List< T >::end() { return LIter< T >(nullptr); }

  template< class T >
  LCIter< T > List< T >::begin() const { return LCIter< T >(head_); }

  template< class T >
  LCIter< T > List< T >::end() const { return LCIter< T >(nullptr); }

  template< class T >
  LIter< T >::LIter(typename List< T >::Node* node): node_(node) {}

  template< class T >
  T& LIter< T >::operator*() { return node_->data_; }

  template< class T >
  T* LIter< T >::operator->() { return &node_->data_; }

  template< class T >
  LIter< T >& LIter< T >::operator++() {
    node_ = node_->next_;
    return *this;
  }

  template< class T >
  bool LIter< T >::operator==(const LIter& other) const { return node_ == other.node_; }

  template< class T >
  bool LIter< T >::operator!=(const LIter& other) const { return node_ != other.node_; }

  template< class T >
  LCIter< T >::LCIter(const typename List< T >::Node* node): node_(node) {}

  template< class T >
  const T& LCIter< T >::operator*() const { return node_->data_; }

  template< class T >
  const T* LCIter< T >::operator->() const { return &node_->data_; }

  template< class T >
  LCIter< T >& LCIter< T >::operator++() {
    node_ = node_->next_;
    return *this;
  }

  template< class T >
  bool LCIter< T >::operator==(const LCIter& other) const { return node_ == other.node_; }

  template< class T >
  bool LCIter< T >::operator!=(const LCIter& other) const { return node_ != other.node_; }
}

#endif
