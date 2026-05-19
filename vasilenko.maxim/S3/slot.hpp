#ifndef VASILENKO_SLOT_HPP
#define VASILENKO_SLOT_HPP

namespace vasilenko {

enum class SlotState {
  Empty,
  Occupied,
  Tombstone
};

template< class Key, class Value >
struct HashNode {
  Key key_;
  Value value_;
  SlotState state_;

  HashNode()
    : state_(SlotState::Empty)
  {}

  HashNode(const Key &k, const Value &v)
    : key_(k),
      value_(v),
      state_(SlotState::Occupied)
  {}
};

}

#endif
