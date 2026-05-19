#ifndef VASILENKO_GRAPH_HPP
#define VASILENKO_GRAPH_HPP

#include "HashTable.hpp"
#include "SipHash.hpp"
#include "Equal.hpp"
#include "vector.hpp"
#include <string>

namespace vasilenko {

class Graph {
public:
  using EdgeMap = HashTable< std::pair< std::string, std::string >, Vector< unsigned int >, PairHash, PairEqual >;

  Graph();
  Graph(const Graph &other) = default;

  void addVertex(const std::string &v);
  void addEdge(const std::string &from, const std::string &to, unsigned int weight);
  void removeEdge(const std::string &from, const std::string &to, unsigned int weight);

  const Vector< std::string >& getVertices() const;
  EdgeMap& getEdges();

  void swap(Graph &other);

private:
  Vector< std::string > vertices_;
  EdgeMap edges_;
};

}

#endif
