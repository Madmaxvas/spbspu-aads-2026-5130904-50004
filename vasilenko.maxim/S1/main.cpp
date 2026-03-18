#include "BiList.hpp"
#include <iostream>
#include <limits>
#include <string>
#include <utility>

int main()
{
  using SeqType = vasilenko_maxim::BiList< unsigned long long >;
  using EntryType = std::pair< std::string, SeqType >;
  using ListType = vasilenko_maxim::BiList< EntryType >;

  ListType data;
  std::string name = "";

  while (std::cin >> name) {
    SeqType seq;
    while (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
      unsigned long long val = 0;
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

  using ValueIter = vasilenko_maxim::LIter< unsigned long long >;
  using IterPair = std::pair< ValueIter, ValueIter >;
  vasilenko_maxim::BiList< IterPair > trackers;

  for (auto it = data.begin(); it != data.end(); ++it) {
    trackers.pushBack(std::make_pair(it->second.begin(), it->second.end()));
  }

  SeqType sums;
  bool processing = true;
  bool overflow = false;

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

        if (!overflow) {
          unsigned long long maxVal = std::numeric_limits< unsigned long long >::max();
          if (rowHasData && (maxVal - currentSum < val)) {
            overflow = true;
          } else {
            currentSum += val;
          }
        }
        rowHasData = true;

        ++(it->first);
        if (it->first != it->second) {
          processing = true;
        }
      }
    }

    if (rowHasData) {
      std::cout << "\n";
      if (overflow) {
        std::cerr << "Overflow\n";
        return 1;
      }
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
