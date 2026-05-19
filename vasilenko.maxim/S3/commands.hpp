#ifndef VASILENKO_COMMANDS_HPP
#define VASILENKO_COMMANDS_HPP

#include "graph.hpp"
#include "HashTable.hpp"
#include "SipHash.hpp"
#include "Equal.hpp"
#include <string>

namespace vasilenko {

class AppContext {
public:
  using GraphMap = HashTable< std::string, Graph, StringHash, StringEqual >;

  void parseInitialFile(const std::string &filename);
  void runInteractive();

private:
  GraphMap graphs_;
 
  void handleGraphs();
  void handleVertexes(const std::string &args);
  void handleOutbound(const std::string &args);
  void handleInbound(const std::string &args);
  void handleBind(const std::string &args);
  void handleCut(const std::string &args);
  void handleCreate(const std::string &args);
  void handleMerge(const std::string &args);
  void handleExtract(const std::string &args);

  Vector< std::string > splitArgs(const std::string &str);
  void sortStrings(Vector< std::string > &vec);
};

}

#endif
