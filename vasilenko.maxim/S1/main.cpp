#include "BiList.hpp"
#include <iostream>
#include <limits>
#include <string>
#include <utility>

int main()
{
  using ListType = vasilenko_maxim::BiList< std::pair< std::string, vasilenko_maxim::BiList< unsigned long long > > >;
  ListType data;
  std::string name;

  while (std::cin >> name) {
    vasilenko_maxim::BiList< unsigned long long > seq;
    while (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
      unsigned long long val;
      if (std::cin >> val) {
        seq.pushBack(val);
      } else {
        std::cin.clear();
        while (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
          std::cin.ignore();
        }
      }
    }
    data.pushBack(std::make_pair(name, std::move(seq)));
  }

  if (data.empty()) {
    std::cout << "0\n";
    return 0;
  }

  for (auto it = data.begin(); it != data.end(); ++it) {
    std::cout << (it == data.begin() ? "" : " ") << it->first;
  }
  std::cout << "\n";

  using IterPair = std::pair< vasilenko_maxim::LIter< unsigned long long >, vasilenko_maxim::LIter< unsigned long long > >;
  vasilenko_maxim::BiList< IterPair > trackers;
  for (auto it = data.begin(); it != data.end(); ++it) {
    trackers.pushBack(std::make_pair(it->second.begin(), it->second.end()));
  }

  vasilenko_maxim::BiList< unsigned long long > sums;
  bool processing = true;
  while (processing) {
    processing = false;
    unsigned long long currentSum = 0;
    bool rowHasData = false;
    bool firstInRow = true;

    for (auto it = trackers.begin(); it != trackers.end(); ++it) {
      if (it->first != it->second) {
        unsigned long long val = *(it->first);
        std::cout << (firstInRow ? "" : " ") << val;
        firstInRow = false;

        if (rowHasData && (std::numeric_limits< unsigned long long >::max() - currentSum < val)) {
          std::cerr << "Overflow\n";
          return 1;
        }
        currentSum += val;
        rowHasData = true;

        ++(it->first);
        if (it->first != it->second) {
          processing = true;
        }
      }
    }
    if (rowHasData) {
      std::cout << "\n";
      sums.pushBack(currentSum);
    }
  }

  if (sums.empty()) {
    std::cout << "0\n";
  } else {
    for (auto it = sums.begin(); it != sums.end(); ++it) {
      std::cout << (it == sums.begin() ? "" : " ") << *it;
    }
    std::cout << "\n";
  }

  return 0;
}
