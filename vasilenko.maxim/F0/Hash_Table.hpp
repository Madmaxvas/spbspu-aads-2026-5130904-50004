#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include "Hash_Table_Iterators.hpp"
#include "Vector.hpp"
#include <functional>
#include <string>

namespace vasilenko {
  template<typename K, typename V>
  class HashTable {
  private:
    using SlotType = detail::HashSlot<K, V>;
    Vector<SlotType> table_;
    std::size_t size_;
    std::size_t capacity_;

    void rehash()
    {
      Vector<SlotType> oldTable = std::move(table_);
      capacity_ *= 2;
      table_.assign(capacity_, SlotType{});
      size_ = 0;
      for (const auto& slot : oldTable) {
        if (slot.status == detail::SlotStatus::OCCUPIED) {
          insert(slot.key, slot.value);
        }
      }
    }

  public:
    using iterator = detail::HashTableIterator<V, typename Vector<SlotType>::iterator>;
    using const_iterator = detail::HashTableConstIterator<V, typename Vector<SlotType>::const_iterator>;

    HashTable(std::size_t initialCapacity = 16)
      : size_(0), capacity_(initialCapacity)
    {
      table_.assign(capacity_, SlotType{});
    }

    void insert(const K& key, const V& value)
    {
      if (size_ >= capacity_ / 2) {
        rehash();
      }
      std::size_t idx = std::hash<K>{}(key) % capacity_;
      while (table_[idx].status == detail::SlotStatus::OCCUPIED) {
        if (table_[idx].key == key) {
          table_[idx].value = value;
          return;
        }
        idx = (idx + 1) % capacity_;
      }
      
      SlotType newSlot{key, value, detail::SlotStatus::OCCUPIED};
      std::swap(table_[idx], newSlot);
      ++size_;
    }

    iterator find(const K& key)
    {
      if (capacity_ == 0) return end();
      std::size_t idx = std::hash<K>{}(key) % capacity_;
      std::size_t startIdx = idx;
      while (table_[idx].status != detail::SlotStatus::EMPTY) {
        if (table_[idx].status == detail::SlotStatus::OCCUPIED && table_[idx].key == key) {
          return iterator(table_.begin() + idx, table_.end());
        }
        idx = (idx + 1) % capacity_;
        if (idx == startIdx) {
          break;
        }
      }
      return end();
    }

    iterator begin() { return iterator(table_.begin(), table_.end()); }
    iterator end() { return iterator(table_.end(), table_.end()); }
    const_iterator begin() const { return const_iterator(table_.begin(), table_.end()); }
    const_iterator end() const { return const_iterator(table_.end(), table_.end()); }
    const_iterator cbegin() const { return const_iterator(table_.cbegin(), table_.cend()); }
    const_iterator cend() const { return const_iterator(table_.cend(), table_.cend()); }
  };
}

#endif
