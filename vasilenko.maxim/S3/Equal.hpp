#ifndef VASILENKO_EQUAL_HPP
#define VASILENKO_EQUAL_HPP

#include <string>
#include <utility>

namespace vasilenko {

struct StringEqual {
  bool operator()(const std::string &lhs, const std::string &rhs) const
  {
    return lhs == rhs;
  }
};

struct PairEqual {
  bool operator()(const std::pair< std::string, std::string > &lhs, const std::pair< std::string, std::string > &rhs) const
  {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }
};

}

#endif
