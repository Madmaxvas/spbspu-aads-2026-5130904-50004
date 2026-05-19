#ifndef VASILENKO_SIPHASH_HPP
#define VASILENKO_SIPHASH_HPP

#include <string>
#include <utility>
#include <cstddef>

namespace vasilenko {

struct StringHash {
  std::size_t operator()(const std::string &str) const
  {
    std::size_t hash = 0;
    for (char c : str) {
      hash = hash * 31 + static_cast< std::size_t >(c);
    }
    return hash;
  }
};

struct PairHash {
  std::size_t operator()(const std::pair< std::string, std::string > &p) const
  {
    StringHash sh;
    std::size_t h1 = sh(p.first);
    std::size_t h2 = sh(p.second);
    return h1 ^ (h2 << 1);
  }
};

}

#endif
