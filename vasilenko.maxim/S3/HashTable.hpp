#ifndef VASILENKO_HASHTABLE_HPP
#define VASILENKO_HASHTABLE_HPP

#include "slot.hpp"
#include "HashTable-iterators.hpp"
#include "vector.hpp"
#include <stdexcept>

namespace vasilenko {

template< class Key, class Value, class Hash, class Equal >
class HashTable {
public:
  using Node = HashNode< Key, Value >;
  using iterator = HashTableIterator< Key, Value >;

  HashTable() : size_(0), tombstones_(0), max_load_factor_(0.7), max_tombstone_factor_(0.2), table_(11) {
  }

  HashTable(std::size_t cap) : size_(0), tombstones_(0), max_load_factor_(0.7), max_tombstone_factor_(0.2), table_(cap > 0 ? cap : 1) {
  }

  HashTable(const HashTable &other) = default;

  HashTable& operator=(HashTable other) {
    swap(other);
    return *this;
  }

  void add(const Key &k, const Value &v) {
    if (getLoadFactor() >= max_load_factor_ || getTombstoneFactor() >= max_tombstone_factor_) {
      rehash(table_.size() * 2);
    }
    std::size_t i = 0;
    std::size_t first_tombstone = table_.size();
    bool found_tombstone = false;

    while (i < table_.size()) {
      std::size_t idx = (hasher_(k) + i * i) % table_.size();
      if (table_[idx].state_ == SlotState::Empty) {
        if (found_tombstone) {
          idx = first_tombstone;
          tombstones_--;
        }
        table_[idx] = Node(k, v);
        size_++;
        return;
      } else if (table_[idx].state_ == SlotState::Occupied && equals_(table_[idx].key_, k)) {
        table_[idx].value_ = v;
        return;
      } else if (table_[idx].state_ == SlotState::Tombstone && !found_tombstone) {
        first_tombstone = idx;
        found_tombstone = true;
      }
      i++;
    }
    throw std::runtime_error("Hash table overflow");
  }

  void drop(const Key &k) {
    std::size_t i = 0;
    while (i < table_.size()) {
      std::size_t idx = (hasher_(k) + i * i) % table_.size();
      if (table_[idx].state_ == SlotState::Empty) {
        throw std::runtime_error("Key not found");
      } else if (table_[idx].state_ == SlotState::Occupied && equals_(table_[idx].key_, k)) {
        table_[idx].state_ = SlotState::Tombstone;
        size_--;
        tombstones_++;
        return;
      }
      i++;
    }
    throw std::runtime_error("Key not found");
  }

  bool has(const Key &k) const {
    std::size_t i = 0;
    while (i < table_.size()) {
      std::size_t idx = (hasher_(k) + i * i) % table_.size();
      if (table_[idx].state_ == SlotState::Empty) {
        return false;
      } else if (table_[idx].state_ == SlotState::Occupied && equals_(table_[idx].key_, k)) {
        return true;
      }
      i++;
    }
    return false;
  }

  Value& get(const Key &k) {
    std::size_t i = 0;
    while (i < table_.size()) {
      std::size_t idx = (hasher_(k) + i * i) % table_.size();
      if (table_[idx].state_ == SlotState::Empty) {
        throw std::runtime_error("Key not found");
      } else if (table_[idx].state_ == SlotState::Occupied && equals_(table_[idx].key_, k)) {
        return table_[idx].value_;
      }
      i++;
    }
    throw std::runtime_error("Key not found");
  }

  void rehash(std::size_t slots) {
    HashTable new_table(slots);
    new_table.setMaxLoadFactor(max_load_factor_);
    new_table.setMaxTombstoneFactor(max_tombstone_factor_);
    for (std::size_t i = 0; i < table_.size(); ++i) {
      if (table_[i].state_ == SlotState::Occupied) {
        new_table.add(table_[i].key_, table_[i].value_);
      }
    }
    swap(new_table);
  }

  double getLoadFactor() const {
    return static_cast< double >(size_) / table_.size();
  }

  double getTombstoneFactor() const {
    return static_cast< double >(tombstones_) / table_.size();
  }

  void setMaxLoadFactor(double max) { max_load_factor_ = max; }
  void setMaxTombstoneFactor(double max) { max_tombstone_factor_ = max; }

  iterator begin() {
    if (table_.size() == 0) return end();
    return iterator(&table_[0], &table_[0] + table_.size());
  }
  iterator end() {
    if (table_.size() == 0) return iterator(nullptr, nullptr);
    return iterator(&table_[0] + table_.size(), &table_[0] + table_.size());
  }

  void swap(HashTable &other) {
    std::swap(size_, other.size_);
    std::swap(tombstones_, other.tombstones_);
    std::swap(max_load_factor_, other.max_load_factor_);
    std::swap(max_tombstone_factor_, other.max_tombstone_factor_);
    table_.swap(other.table_);
  }

private:
  std::size_t size_;
  std::size_t tombstones_;
  double max_load_factor_;
  double max_tombstone_factor_;
  Vector< Node > table_;
  Hash hasher_;
  Equal equals_;
};

}

#endif
