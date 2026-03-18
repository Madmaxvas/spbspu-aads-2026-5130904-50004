#ifndef VASILENKO_MAXIM_LIST_HPP
#define VASILENKO_MAXIM_LIST_HPP

#include <cstddef>
#include <algorithm>

namespace vasilenko_maxim
{
  template< typename T >
  class Bilist
  {
    struct List
    {
      T data;
      List * prev;
      List * next;

      List(const T & val, List * p, List * n):
        data(val),
        prev(p),
        next(n)
      {}
    };

  public:
    using value_type = T;

    template< typename U >
    class BasicIterator
    {
      friend class Bilist< T >;
    public:
      using iterator_category = std::bidirectional_iterator_tag;
      using value_type = U;
      using difference_type = std::ptrdiff_t;
      using pointer = U *;
      using reference = U &;

      BasicIterator(): node_(nullptr) {}
      explicit BasicIterator(List * node): node_(node) {}

      reference operator*() const { return node_->data; }
      pointer operator->() const { return &node_->data; }

      BasicIterator & operator++()
      {
        node_ = node_->next;
        return *this;
      }

      BasicIterator operator++(int)
      {
        BasicIterator temp = *this;
        node_ = node_->next;
        return temp;
      }

      BasicIterator & operator--()
      {
        node_ = node_->prev;
        return *this;
      }

      BasicIterator operator--(int)
      {
        BasicIterator temp = *this;
        node_ = node_->prev;
        return temp;
      }

      bool operator==(const BasicIterator & other) const { return node_ == other.node_; }
      bool operator!=(const BasicIterator & other) const { return node_ != other.node_; }

    private:
      List * node_;
    };

    using iterator = BasicIterator< T >;
    using const_iterator = BasicIterator< const T >;

    Bilist(): head_(nullptr), tail_(nullptr) {}

    Bilist(const Bilist & other): head_(nullptr), tail_(nullptr)
    {
      for (const_iterator it = other.begin(); it != other.end(); ++it)
      {
        pushBack(*it);
      }
    }

    Bilist(Bilist && other) noexcept: head_(other.head_), tail_(other.tail_)
    {
      other.head_ = nullptr;
      other.tail_ = nullptr;
    }

    ~Bilist() { clear(); }

    Bilist & operator=(const Bilist & other)
    {
      if (this != &other)
      {
        Bilist temp(other);
        std::swap(head_, temp.head_);
        std::swap(tail_, temp.tail_);
      }
      return *this;
    }

    Bilist & operator=(Bilist && other) noexcept
    {
      if (this != &other)
      {
        clear();
        head_ = other.head_;
        tail_ = other.tail_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
      }
      return *this;
    }

    void pushBack(const T & val)
    {
      List * newNode = new List(val, tail_, nullptr);
      if (tail_)
      {
        tail_->next = newNode;
      }
      else
      {
        head_ = newNode;
      }
      tail_ = newNode;
    }

    void popFront()
    {
      if (head_)
      {
        List * temp = head_;
        head_ = head_->next;
        if (head_)
        {
          head_->prev = nullptr;
        }
        else
        {
          tail_ = nullptr;
        }
        delete temp;
      }
    }

    void clear()
    {
      while (!isEmpty())
      {
        popFront();
      }
    }

    bool isEmpty() const { return head_ == nullptr; }
    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(nullptr); }
    const_iterator begin() const { return const_iterator(head_); }
    const_iterator end() const { return const_iterator(nullptr); }

    T & front() { return head_->data; }
    const T & front() const { return head_->data; }

  private:
    List * head_;
    List * tail_;
  };
}

#endif
