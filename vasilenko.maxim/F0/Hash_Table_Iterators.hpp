#ifndef HASH_TABLE_ITERATORS_HPP
#define HASH_TABLE_ITERATORS_HPP

#include <cstddef>
#include <iterator>

namespace vasilenko {
  namespace detail {

    enum class SlotStatus { EMPTY, OCCUPIED, DELETED };

    template<typename K, typename V>
    struct HashSlot {
      K key;
      V value;
      SlotStatus status = SlotStatus::EMPTY;
    };

    template<typename V, typename SlotIterator>
    class HashTableIterator {
    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = V;
      using difference_type = std::ptrdiff_t;
      using pointer = V*;
      using reference = V&;

    private:
      SlotIterator current_;
      SlotIterator end_;

      void advanceToOccupied()
      {
        while (current_ != end_ && current_->status != SlotStatus::OCCUPIED) {
          ++current_;
        }
      }

    public:
      HashTableIterator(SlotIterator start, SlotIterator end)
        : current_(start), end_(end)
      {
        advanceToOccupied();
      }

      reference operator*() { return current_->value; }
      pointer operator->() { return &(current_->value); }

      HashTableIterator& operator++()
      {
        ++current_;
        advanceToOccupied();
        return *this;
      }

      HashTableIterator operator++(int)
      {
        HashTableIterator tmp = *this;
        ++(*this);
        return tmp;
      }

      bool operator==(const HashTableIterator& other) const { return current_ == other.current_; }
      bool operator!=(const HashTableIterator& other) const { return current_ != other.current_; }
    };

    template<typename V, typename SlotConstIterator>
    class HashTableConstIterator {
    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = const V;
      using difference_type = std::ptrdiff_t;
      using pointer = const V*;
      using reference = const V&;

    private:
      SlotConstIterator current_;
      SlotConstIterator end_;

      void advanceToOccupied()
      {
        while (current_ != end_ && current_->status != SlotStatus::OCCUPIED) {
          ++current_;
        }
      }

    public:
      HashTableConstIterator(SlotConstIterator start, SlotConstIterator end)
        : current_(start), end_(end)
      {
        advanceToOccupied();
      }

      reference operator*() const { return current_->value; }
      pointer operator->() const { return &(current_->value); }

      HashTableConstIterator& operator++()
      {
        ++current_;
        advanceToOccupied();
        return *this;
      }

      HashTableConstIterator operator++(int)
      {
        HashTableConstIterator tmp = *this;
        ++(*this);
        return tmp;
      }

      bool operator==(const HashTableConstIterator& other) const { return current_ == other.current_; }
      bool operator!=(const HashTableConstIterator& other) const { return current_ != other.current_; }
    };

  }
}

#endif
