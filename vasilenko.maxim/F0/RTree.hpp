#ifndef RTREE_HPP
#define RTREE_HPP

#include "Location.hpp"
#include "RTree_Iterators.hpp"
#include "Vector.hpp"
#include <algorithm>
#include <memory>

namespace vasilenko {
  namespace detail {

    struct BoundingBox {
      int minX = 0;
      int minY = 0;
      int maxX = 0;
      int maxY = 0;

      void expand(const Location& loc)
      {
        minX = std::min(minX, loc.minX);
        minY = std::min(minY, loc.minY);
        maxX = std::max(maxX, loc.maxX);
        maxY = std::max(maxY, loc.maxY);
      }

      void expand(const BoundingBox& other)
      {
        minX = std::min(minX, other.minX);
        minY = std::min(minY, other.minY);
        maxX = std::max(maxX, other.maxX);
        maxY = std::max(maxY, other.maxY);
      }

      long long area() const
      {
        return static_cast<long long>(maxX - minX) * (maxY - minY);
      }

      bool contains(int x, int y) const
      {
        return x >= minX && x <= maxX && y >= minY && y <= maxY;
      }
    };

    struct RTreeNode {
      bool isLeaf = true;
      BoundingBox box;
      Vector<Location> locations;
      Vector<std::shared_ptr<RTreeNode>> children;
    };

  }

  class RTree {
  private:
    static const int MAX_ENTRIES = 4;
    std::shared_ptr<detail::RTreeNode> root_;

    void updateBoundingBox(std::shared_ptr<detail::RTreeNode> node);
    std::shared_ptr<detail::RTreeNode> chooseLeaf(std::shared_ptr<detail::RTreeNode> node, const Location& loc);
    void splitNode(std::shared_ptr<detail::RTreeNode> node, std::shared_ptr<detail::RTreeNode> parent);

  public:
    using iterator = detail::RTreeIterator;
    using const_iterator = detail::RTreeConstIterator;

    RTree();
    void insert(const Location& loc);
    Vector<Location*> findIntersections(int x, int y);

    iterator begin() { return iterator(root_, false); }
    iterator end() { return iterator(root_, true); }
    const_iterator begin() const { return const_iterator(root_, false); }
    const_iterator end() const { return const_iterator(root_, true); }
    const_iterator cbegin() const { return const_iterator(root_, false); }
    const_iterator cend() const { return const_iterator(root_, true); }
  };

}

#endif
