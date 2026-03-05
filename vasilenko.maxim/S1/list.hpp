#ifndef VASILENKO_MAXIM_LIST_HPP
#define VASILENKO_MAXIM_LIST_HPP

namespace vasilenko_maxim {

template<class T>
class LIter;

template<class T>
class LCIter;

template<class T>
class List {
public:
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

  LIter<T> begin();
  LIter<T> end();
  LCIter<T> begin() const;
  LCIter<T> end() const;

private:
  struct Node {
    T data_;
    Node* prev_;
    Node* next_;

    Node(const T& data, Node* prev, Node* next);
  };

  Node* head_;
  Node* tail_;

  friend class LIter<T>;
  friend class LCIter<T>;
};

template<class T>
class LIter {
public:
  LIter(typename List<T>::Node* node);

  T& operator*();
  LIter& operator++();
  LIter& operator--();
  bool operator==(const LIter& other) const;
  bool operator!=(const LIter& other) const;

private:
  typename List<T>::Node* node_;
};

template<class T>
class LCIter {
public:
  LCIter(const typename List<T>::Node* node);

  const T& operator*() const;
  LCIter& operator++();
  LCIter& operator--();
  bool operator==(const LCIter& other) const;
  bool operator!=(const LCIter& other) const;

private:
  const typename List<T>::Node* node_;
};

}

template<class T>
vasilenko_maxim::List<T>::Node::Node(const T& data, Node* prev, Node* next):
  data_(data),
  prev_(prev),
  next_(next)
{
}

template<class T>
vasilenko_maxim::List<T>::List():
  head_(nullptr),
  tail_(nullptr)
{
}

template<class T>
vasilenko_maxim::List<T>::List(const List& other):
  head_(nullptr),
  tail_(nullptr)
{
  for (auto it = other.begin(); it != other.end(); ++it) {
    pushBack(*it);
  }
}

template<class T>
vasilenko_maxim::List<T>::List(List&& other) noexcept:
  head_(other.head_),
  tail_(other.tail_)
{
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template<class T>
vasilenko_maxim::List<T>::~List()
{
  clear();
}

template<class T>
vasilenko_maxim::List<T>& vasilenko_maxim::List<T>::operator=(const List& other)
{
  if (this != &other) {
    clear();
    for (vasilenko_maxim::LCIter<T> it = other.begin(); it != other.end(); ++it) {
      pushBack(*it);
    }
  }
  return *this;
}

template<class T>
vasilenko_maxim::List<T>& vasilenko_maxim::List<T>::operator=(List&& other) noexcept
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

template<class T>
void vasilenko_maxim::List<T>::pushBack(const T& value)
{
  Node* newNode = new Node(value, tail_, nullptr);
  if (tail_ != nullptr) {
    tail_->next_ = newNode;
  }
  tail_ = newNode;
  if (head_ == nullptr) {
    head_ = newNode;
  }
}

template<class T>
void vasilenko_maxim::List<T>::pushFront(const T& value)
{
  Node* newNode = new Node(value, nullptr, head_);
  if (head_ != nullptr) {
    head_->prev_ = newNode;
  }
  head_ = newNode;
  if (tail_ == nullptr) {
    tail_ = newNode;
  }
}

template<class T>
void vasilenko_maxim::List<T>::popBack()
{
  if (tail_ != nullptr) {
    Node* prevNode = tail_->prev_;
    delete tail_;
    tail_ = prevNode;
    if (tail_ != nullptr) {
      tail_->next_ = nullptr;
    } else {
      head_ = nullptr;
    }
  }
}

template<class T>
void vasilenko_maxim::List<T>::popFront()
{
  if (head_ != nullptr) {
    Node* nextNode = head_->next_;
    delete head_;
    head_ = nextNode;
    if (head_ != nullptr) {
      head_->prev_ = nullptr;
    } else {
      tail_ = nullptr;
    }
  }
}

template<class T>
void vasilenko_maxim::List<T>::clear()
{
  Node* current = head_;
  while (current != nullptr) {
    Node* next = current->next_;
    delete current;
    current = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template<class T>
bool vasilenko_maxim::List<T>::isEmpty() const
{
  return head_ == nullptr;
}

template<class T>
T& vasilenko_maxim::List<T>::front()
{
  return head_->data_;
}

template<class T>
const T& vasilenko_maxim::List<T>::front() const
{
  return head_->data_;
}

template<class T>
T& vasilenko_maxim::List<T>::back()
{
  return tail_->data_;
}

template<class T>
const T& vasilenko_maxim::List<T>::back() const
{
  return tail_->data_;
}

template<class T>
vasilenko_maxim::LIter<T> vasilenko_maxim::List<T>::begin()
{
  return LIter<T>(head_);
}

template<class T>
vasilenko_maxim::LIter<T> vasilenko_maxim::List<T>::end()
{
  return LIter<T>(nullptr);
}

template<class T>
vasilenko_maxim::LCIter<T> vasilenko_maxim::List<T>::begin() const
{
  return LCIter<T>(head_);
}

template<class T>
vasilenko_maxim::LCIter<T> vasilenko_maxim::List<T>::end() const
{
  return LCIter<T>(nullptr);
}

template<class T>
vasilenko_maxim::LIter<T>::LIter(typename List<T>::Node* node):
  node_(node)
{
}

template<class T>
T& vasilenko_maxim::LIter<T>::operator*()
{
  return node_->data_;
}

template<class T>
vasilenko_maxim::LIter<T>& vasilenko_maxim::LIter<T>::operator++()
{
  node_ = node_->next_;
  return *this;
}

template<class T>
vasilenko_maxim::LIter<T>& vasilenko_maxim::LIter<T>::operator--()
{
  node_ = node_->prev_;
  return *this;
}

template<class T>
bool vasilenko_maxim::LIter<T>::operator==(const LIter& other) const
{
  return node_ == other.node_;
}

template<class T>
bool vasilenko_maxim::LIter<T>::operator!=(const LIter& other) const
{
  return node_ != other.node_;
}

template<class T>
vasilenko_maxim::LCIter<T>::LCIter(const typename List<T>::Node* node):
  node_(node)
{
}

template<class T>
const T& vasilenko_maxim::LCIter<T>::operator*() const
{
  return node_->data_;
}

template<class T>
vasilenko_maxim::LCIter<T>& vasilenko_maxim::LCIter<T>::operator++()
{
  node_ = node_->next_;
  return *this;
}

template<class T>
vasilenko_maxim::LCIter<T>& vasilenko_maxim::LCIter<T>::operator--()
{
  node_ = node_->prev_;
  return *this;
}

template<class T>
bool vasilenko_maxim::LCIter<T>::operator==(const LCIter& other) const
{
  return node_ == other.node_;
}

template<class T>
bool vasilenko_maxim::LCIter<T>::operator!=(const LCIter& other) const
{
  return node_ != other.node_;
}

#endif
