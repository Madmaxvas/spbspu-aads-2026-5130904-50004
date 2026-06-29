#ifndef RTREE_ITERATORS_HPP
#define RTREE_ITERATORS_HPP

#include "Location.hpp"
#include "Vector.hpp"
#include <cstddef>
#include <iterator>

namespace vasilenko {
  namespace detail {
    struct RTreeNode;

    class RTreeIterator {
    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = Location;
      using difference_type = std::ptrdiff_t;
      using pointer = Location*;
      using reference = Location&;

    private:
      Vector<RTreeNode*> nodeStack_;
      std::size_t locIndex_;
      Location* currentLoc_;
      void advance();

    public:
      RTreeIterator(RTreeNode* root, bool isEnd);
      reference operator*() { return *currentLoc_; }
      pointer operator->() { return currentLoc_; }
      RTreeIterator& operator++();
      RTreeIterator operator++(int);
      bool operator==(const RTreeIterator& other) const { return currentLoc_ == other.currentLoc_; }
      bool operator!=(const RTreeIterator& other) const { return currentLoc_ != other.currentLoc_; }
    };

    class RTreeConstIterator {
    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = const Location;
      using difference_type = std::ptrdiff_t;
      using pointer = const Location*;
      using reference = const Location&;

    private:
      Vector<const RTreeNode*> nodeStack_;
      std::size_t locIndex_;
      const Location* currentLoc_;
      void advance();

    public:
      RTreeConstIterator(const RTreeNode* root, bool isEnd);
      reference operator*() const { return *currentLoc_; }
      pointer operator->() const { return currentLoc_; }
      RTreeConstIterator& operator++();
      RTreeConstIterator operator++(int);
      bool operator==(const RTreeConstIterator& other) const { return currentLoc_ == other.currentLoc_; }
      bool operator!=(const RTreeConstIterator& other) const { return currentLoc_ != other.currentLoc_; }
    };
  }
}

#endif
