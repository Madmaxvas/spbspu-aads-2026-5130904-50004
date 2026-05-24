#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <utility>

namespace vasilenko {

template<class Key, class Value>
struct TreeNode {
  using PairType = std::pair<const Key, Value>;

  PairType data_;
  TreeNode* left_;
  TreeNode* right_;
  TreeNode* parent_;

  TreeNode(const Key& k, const Value& v, TreeNode* p = nullptr):
    data_(k, v),
    left_(nullptr),
    right_(nullptr),
    parent_(p)
  {
  }
};

}

#endif
