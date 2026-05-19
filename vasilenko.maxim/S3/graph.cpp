#include "graph.hpp"

namespace vasilenko {

Graph::Graph() : vertices_(), edges_(20) {}

void Graph::addVertex(const std::string &v)
{
  bool found = false;
  for (std::size_t i = 0; i < vertices_.size(); ++i) {
    if (vertices_[i] == v) {
      found = true;
      break;
    }
  }
  if (!found) {
    vertices_.push_back(v);
  }
}

void Graph::addEdge(const std::string &from, const std::string &to, unsigned int weight)
{
  Graph backup = *this;
  try {
    addVertex(from);
    addVertex(to);

    std::pair< std::string, std::string > edge(from, to);
    if (edges_.has(edge)) {
      edges_.get(edge).push_back(weight);
    } else {
      Vector< unsigned int > weights;
      weights.push_back(weight);
      edges_.add(edge, weights);
    }
  } catch (...) {
    swap(backup);
    throw;
  }
}

void Graph::removeEdge(const std::string &from, const std::string &to, unsigned int weight)
{
  std::pair< std::string, std::string > edge(from, to);
  if (!edges_.has(edge)) {
    throw std::runtime_error("Edge not found");
  }
  Vector< unsigned int > &weights = edges_.get(edge);
  bool found = false;
  Vector< unsigned int > new_weights;
  for (std::size_t i = 0; i < weights.size(); ++i) {
    if (weights[i] == weight && !found) {
      found = true;
    } else {
      new_weights.push_back(weights[i]);
    }
  }
  if (!found) throw std::runtime_error("Weight not found");
  if (new_weights.size() == 0) {
    edges_.drop(edge);
  } else {
    weights = new_weights;
  }
}

const Vector< std::string >& Graph::getVertices() const
{
  return vertices_;
}

Graph::EdgeMap& Graph::getEdges()
{
  return edges_;
}

void Graph::swap(Graph &other)
{
  vertices_.swap(other.vertices_);
  edges_.swap(other.edges_);
}

}
