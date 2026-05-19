#include "commands.hpp"
#include <iostream>
#include <fstream>

namespace vasilenko {

void AppContext::sortStrings(Vector< std::string > &vec)
{
  for (std::size_t i = 0; i < vec.size(); ++i) {
    for (std::size_t j = i + 1; j < vec.size(); ++j) {
      if (vec[j] < vec[i]) {
        std::string tmp = vec[i];
        vec[i] = vec[j];
        vec[j] = tmp;
      }
    }
  }
}

Vector< std::string > AppContext::splitArgs(const std::string &str)
{
  Vector< std::string > args;
  std::string current;
  for (char c : str) {
    if (c == ' ' || c == '\\t' || c == '\\r') {
      if (!current.empty()) {
        args.push_back(current);
        current.clear();
      }
    } else {
      current += c;
    }
  }
  if (!current.empty()) {
    args.push_back(current);
  }
  return args;
}

void AppContext::parseInitialFile(const std::string &filename)
{
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file");
  }
  std::string line;
  while (std::getline(file, line)) {
    Vector< std::string > tokens = splitArgs(line);
    if (tokens.size() == 2) {
      std::string g_name = tokens[0];
      int edges_count = std::stoi(tokens[1]);
      Graph g;
      for (int i = 0; i < edges_count; ++i) {
        std::string edge_line;
        if (!std::getline(file, edge_line)) break;
        Vector< std::string > e_tokens = splitArgs(edge_line);
        if (e_tokens.size() == 3) {
          g.addEdge(e_tokens[0], e_tokens[1], std::stoi(e_tokens[2]));
        }
      }
      graphs_.add(g_name, g);
    }
  }
}

void AppContext::handleGraphs()
{
  Vector< std::string > names;
  for (auto it = graphs_.begin(); it != graphs_.end(); ++it) {
    names.push_back(it->key_);
  }
  sortStrings(names);
  for (std::size_t i = 0; i < names.size(); ++i) {
    std::cout << names[i] << "\\n";
  }
}

void AppContext::handleVertexes(const std::string &args)
{
  Vector< std::string > tokens = splitArgs(args);
  if (tokens.size() != 1 || !graphs_.has(tokens[0])) {
    std::cout << "<INVALID COMMAND>\\n";
    return;
  }
  Vector< std::string > verts = graphs_.get(tokens[0]).getVertices();
  sortStrings(verts);
  for (std::size_t i = 0; i < verts.size(); ++i) {
    std::cout << verts[i] << "\\n";
  }
}

void AppContext::handleOutbound(const std::string &args)
{
  Vector< std::string > tokens = splitArgs(args);
  if (tokens.size() != 2 || !graphs_.has(tokens[0])) {
    std::cout << "<INVALID COMMAND>\\n";
    return;
  }
  std::string v = tokens[1];
  Graph &g = graphs_.get(tokens[0]);
  Graph::EdgeMap &edges = g.getEdges();

  Vector< std::string > out_v;
  for (auto it = edges.begin(); it != edges.end(); ++it) {
    if (it->key_.first == v) {
      out_v.push_back(it->key_.second);
    }
  }
  sortStrings(out_v);

  for (std::size_t i = 0; i < out_v.size(); ++i) {
    std::pair< std::string, std::string > key(v, out_v[i]);
    Vector< unsigned int > w = edges.get(key);
    for (std::size_t j = 0; j < w.size(); ++j) {
      for (std::size_t k = j + 1; k < w.size(); ++k) {
        if (w[k] < w[j]) std::swap(w[j], w[k]);
      }
    }
    std::cout << out_v[i];
    for (std::size_t j = 0; j < w.size(); ++j) std::cout << " " << w[j];
    std::cout << "\\n";
  }
}

void AppContext::handleInbound(const std::string &args)
{
  Vector< std::string > tokens = splitArgs(args);
  if (tokens.size() != 2 || !graphs_.has(tokens[0])) {
    std::cout << "<INVALID COMMAND>\\n";
    return;
  }
  std::string v = tokens[1];
  Graph &g = graphs_.get(tokens[0]);
  Graph::EdgeMap &edges = g.getEdges();

  Vector< std::string > in_v;
  for (auto it = edges.begin(); it != edges.end(); ++it) {
    if (it->key_.second == v) {
      in_v.push_back(it->key_.first);
    }
  }
  sortStrings(in_v);

  for (std::size_t i = 0; i < in_v.size(); ++i) {
    std::pair< std::string, std::string > key(in_v[i], v);
    Vector< unsigned int > w = edges.get(key);
    for (std::size_t j = 0; j < w.size(); ++j) {
      for (std::size_t k = j + 1; k < w.size(); ++k) {
        if (w[k] < w[j]) std::swap(w[j], w[k]);
      }
    }
    std::cout << in_v[i];
    for (std::size_t j = 0; j < w.size(); ++j) std::cout << " " << w[j];
    std::cout << "\\n";
  }
}

void AppContext::handleBind(const std::string &args)
{
  Vector< std::string > tokens = splitArgs(args);
  if (tokens.size() != 4 || !graphs_.has(tokens[0])) {
    std::cout << "<INVALID COMMAND>\\n";
    return;
  }
  try {
    unsigned int weight = std::stoi(tokens[3]);
    graphs_.get(tokens[0]).addEdge(tokens[1], tokens[2], weight);
  } catch (...) {
    std::cout << "<INVALID COMMAND>\\n";
  }
}

void AppContext::handleCut(const std::string &args)
{
  Vector< std::string > tokens = splitArgs(args);
  if (tokens.size() != 4 || !graphs_.has(tokens[0])) {
    std::cout << "<INVALID COMMAND>\\n";
    return;
  }
  try {
    unsigned int weight = std::stoi(tokens[3]);
    graphs_.get(tokens[0]).removeEdge(tokens[1], tokens[2], weight);
  } catch (...) {
    std::cout << "<INVALID COMMAND>\\n";
  }
}

void AppContext::handleCreate(const std::string &args)
{
  Vector< std::string > tokens = splitArgs(args);
  if (tokens.size() < 2 || graphs_.has(tokens[0])) {
    std::cout << "<INVALID COMMAND>\\n";
    return;
  }
  Graph g;
  int k = std::stoi(tokens[1]);
  if (tokens.size() != static_cast<std::size_t>(2 + k)) {
    std::cout << "<INVALID COMMAND>\\n";
    return;
  }
  for (int i = 0; i < k; ++i) {
    g.addVertex(tokens[2 + i]);
  }
  graphs_.add(tokens[0], g);
}

void AppContext::handleMerge(const std::string &args)
{
  Vector< std::string > tokens = splitArgs(args);
  if (tokens.size() != 3 || graphs_.has(tokens[0]) || !graphs_.has(tokens[1]) || !graphs_.has(tokens[2])) {
    std::cout << "<INVALID COMMAND>\\n";
    return;
  }
  Graph g;
  Graph &g1 = graphs_.get(tokens[1]);
  Graph &g2 = graphs_.get(tokens[2]);

  Vector< std::string > v1 = g1.getVertices();
  for (std::size_t i = 0; i < v1.size(); ++i) g.addVertex(v1[i]);
  Vector< std::string > v2 = g2.getVertices();
  for (std::size_t i = 0; i < v2.size(); ++i) g.addVertex(v2[i]);

  for (auto it = g1.getEdges().begin(); it != g1.getEdges().end(); ++it) {
    for (std::size_t w = 0; w < it->value_.size(); ++w) g.addEdge(it->key_.first, it->key_.second, it->value_[w]);
  }
  for (auto it = g2.getEdges().begin(); it != g2.getEdges().end(); ++it) {
    for (std::size_t w = 0; w < it->value_.size(); ++w) g.addEdge(it->key_.first, it->key_.second, it->value_[w]);
  }
  graphs_.add(tokens[0], g);
}

void AppContext::handleExtract(const std::string &args)
{
  Vector< std::string > tokens = splitArgs(args);
  if (tokens.size() < 3 || graphs_.has(tokens[0]) || !graphs_.has(tokens[1])) {
    std::cout << "<INVALID COMMAND>\\n";
    return;
  }
  int k = std::stoi(tokens[2]);
  if (tokens.size() != static_cast<std::size_t>(3 + k)) {
    std::cout << "<INVALID COMMAND>\\n";
    return;
  }
  Graph &old_g = graphs_.get(tokens[1]);
  Graph g;
  Vector< std::string > target_verts;
  for (int i = 0; i < k; ++i) {
    g.addVertex(tokens[3 + i]);
    target_verts.push_back(tokens[3 + i]);
  }

  for (auto it = old_g.getEdges().begin(); it != old_g.getEdges().end(); ++it) {
    bool found_from = false, found_to = false;
    for (std::size_t i = 0; i < target_verts.size(); ++i) {
      if (it->key_.first == target_verts[i]) found_from = true;
      if (it->key_.second == target_verts[i]) found_to = true;
    }
    if (found_from && found_to) {
      for (std::size_t w = 0; w < it->value_.size(); ++w) g.addEdge(it->key_.first, it->key_.second, it->value_[w]);
    }
  }
  graphs_.add(tokens[0], g);
}

void AppContext::runInteractive()
{
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) continue;
    std::size_t space_pos = line.find(' ');
    std::string cmd = line.substr(0, space_pos);
    std::string args = space_pos == std::string::npos ? "" : line.substr(space_pos + 1);

    if (cmd == "graphs") handleGraphs();
    else if (cmd == "vertexes") handleVertexes(args);
    else if (cmd == "outbound") handleOutbound(args);
    else if (cmd == "inbound") handleInbound(args);
    else if (cmd == "bind") handleBind(args);
    else if (cmd == "cut") handleCut(args);
    else if (cmd == "create") handleCreate(args);
    else if (cmd == "merge") handleMerge(args);
    else if (cmd == "extract") handleExtract(args);
    else std::cout << "<INVALID COMMAND>\\n";
  }
}

}
