#ifndef BILIST_HPP
#define BILIST_HPP

#include <cstddef>
#include <algorithm>
#include <iterator>

namespace vasilenko_maxim
{
  template< typename T >
  class BiList
  {
    struct Node
    {
      T val;
      Node * next;
      Node * prev;

      Node(const T & value):
        val(value),
        next(nullptr),
        prev(nullptr)
      {}
    };

    Node * head;
    Node * tail;
    size_t size_;

  public:
    class BIter
    {
      Node * node;
      friend class BiList< T >;
    public:
      using iterator_category = std::bidirectional_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = T *;
      using reference = T &;

      BIter(Node * n = nullptr): node(n) {}

      reference operator*() const { return node->val; }
      pointer operator->() const { return &(node->val); }

      BIter & operator++() { node = node->next; return *this; }
      BIter operator++(int) { BIter tmp = *this; node = node->next; return tmp; }
      BIter & operator--() { node = node->prev; return *this; }
      BIter operator--(int) { BIter tmp = *this; node = node->prev; return tmp; }

      bool operator==(const BIter & x) const { return node == x.node; }
      bool operator!=(const BIter & x) const { return node != x.node; }
    };

    BiList(): head(nullptr), tail(nullptr), size_(0) {}

    ~BiList() { clear(); }

    // Реализация Rule of Three/Five должна быть здесь...
    // (методы push_back, push_front, pop_front, clear как в предыдущем ответе)

    void push_back(const T & d)
    {
      Node * newNode = new Node(d);
      if (!tail)
      {
        head = tail = newNode;
      }
      else
      {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
      }
      size_++;
    }

    void clear() noexcept
    {
      while (head)
      {
        Node * temp = head;
        head = head->next;
        delete temp;
      }
      tail = nullptr;
      size_ = 0;
    }

    size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return head == nullptr; }
    BIter begin() { return BIter(head); }
    BIter end() { return BIter(nullptr); }
  };
}

#endif
