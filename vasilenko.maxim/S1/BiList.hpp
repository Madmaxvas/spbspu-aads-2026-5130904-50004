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

      BIter(Node * n = nullptr):
        node(n)
      {}

      reference operator*() const
      {
        return node->val;
      }

      pointer operator->() const
      {
        return &(node->val);
      }

      BIter & operator++()
      {
        node = node->next;
        return *this;
      }

      BIter operator++(int)
      {
        BIter tmp = *this;
        node = node->next;
        return tmp;
      }

      BIter & operator--()
      {
        node = node->prev;
        return *this;
      }

      BIter operator--(int)
      {
        BIter tmp = *this;
        node = node->prev;
        return tmp;
      }

      bool operator==(const BIter & x) const
      {
        return node == x.node;
      }

      bool operator!=(const BIter & x) const
      {
        return node != x.node;
      }
    };

    BiList():
      head(nullptr),
      tail(nullptr),
      size_(0)
    {}

    BiList(const BiList & other):
      head(nullptr),
      tail(nullptr),
      size_(0)
    {
      for (Node * curr = other.head; curr; curr = curr->next)
      {
        push_back(curr->val);
      }
    }

    BiList(BiList && other) noexcept:
      head(other.head),
      tail(other.tail),
      size_(other.size_)
    {
      other.head = nullptr;
      other.tail = nullptr;
      other.size_ = 0;
    }

    ~BiList()
    {
      clear();
    }

    BiList & operator=(const BiList & other)
    {
      if (this != &other)
      {
        BiList tmp(other);
        std::swap(head, tmp.head);
        std::swap(tail, tmp.tail);
        std::swap(size_, tmp.size_);
      }
      return *this;
    }

    BiList & operator=(BiList && other) noexcept
    {
      if (this != &other)
      {
        clear();
        head = other.head;
        tail = other.tail;
        size_ = other.size_;
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
      }
      return *this;
    }

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

    void push_front(const T & d)
    {
      Node * newNode = new Node(d);
      if (!head)
      {
        head = tail = newNode;
      }
      else
      {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
      }
      size_++;
    }

    void pop_front() noexcept
    {
      if (!head)
      {
        return;
      }
      Node * temp = head;
      head = head->next;
      if (head)
      {
        head->prev = nullptr;
      }
      else
      {
        tail = nullptr;
      }
      delete temp;
      size_--;
    }

    void pop_back() noexcept
    {
      if (!tail)
      {
        return;
      }
      Node * temp = tail;
      tail = tail->prev;
      if (tail)
      {
        tail->next = nullptr;
      }
      else
      {
        head = nullptr;
      }
      delete temp;
      size_--;
    }

    void clear() noexcept
    {
      while (head)
      {
        pop_front();
      }
    }

    size_t size() const noexcept
    {
      return size_;
    }

    bool empty() const noexcept
    {
      return head == nullptr;
    }

    T & front()
    {
      return head->val;
    }

    const T & front() const
    {
      return head->val;
    }

    T & back()
    {
      return tail->val;
    }

    const T & back() const
    {
      return tail->val;
    }

    BIter begin()
    {
      return BIter(head);
    }

    BIter end()
    {
      return BIter(nullptr);
    }
  };
}

#endif
