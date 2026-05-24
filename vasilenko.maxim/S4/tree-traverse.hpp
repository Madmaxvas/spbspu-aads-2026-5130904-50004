#ifndef TREE_TRAVERSE_HPP
#define TREE_TRAVERSE_HPP

#include <algorithm>
#include <cstddef>

namespace vasilenko {

template<class Node>
void clearTree(Node* node)
{
  if (node != nullptr) {
    clearTree(node->left_);
    clearTree(node->right_);
    delete node;
  }
}

template<class Node>
std::size_t calculateHeight(Node* node)
{
  if (node == nullptr) {
    return 0;
  }
  return 1 + std::max(calculateHeight(node->left_), calculateHeight(node->right_));
}

}

#endif
