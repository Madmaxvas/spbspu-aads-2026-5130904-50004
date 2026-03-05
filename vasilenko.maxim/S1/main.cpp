#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"

struct NamedList {
  std::string name;
  vasilenko_maxim::List< unsigned long long > numbers;
};

int main()
{
  using namespace vasilenko_maxim;
  List< NamedList > allSeqs;
  std::string name;

  while (std::cin >> name) {
    NamedList current;
    current.name = name;

    while (true) {
      int c = std::cin.peek();
      if (c == '\n' || c == std::char_traits< char >::eof()) {
        if (c == '\n') {
          std::cin.get();
        }
        break;
      }
      if (std::isspace(c)) {
        std::cin.get();
        continue;
      }

      unsigned long long val = 0;
      if (std::cin >> val) {
        current.numbers.pushBack(val);
      } else {
        std::cerr << "Overflow error\n";
        return 1;
      }
    }
    allSeqs.pushBack(current);
  }

  if (allSeqs.isEmpty()) {
    std::cout << "0\n";
    return 0;
  }

  bool first = true;
  for (LIter< NamedList > it = allSeqs.begin(); it != allSeqs.end(); ++it) {
    if (!first) {
      std::cout << " ";
    }
    std::cout << it->name;
    first = false;
  }
  std::cout << "\n";

  List< unsigned long long > rowSums;
  bool hasData = true;
  while (hasData) {
    hasData = false;
    unsigned long long currentSum = 0;
    bool firstInRow = true;

    for (LIter< NamedList > it = allSeqs.begin(); it != allSeqs.end(); ++it) {
      if (!it->numbers.isEmpty()) {
        if (!firstInRow) {
          std::cout << " ";
        }
        unsigned long long val = it->numbers.front();
        std::cout << val;

        if (std::numeric_limits< unsigned long long >::max() - currentSum < val) {
          std::cerr << "Overflow error\n";
          return 1;
        }
        currentSum += val;
        it->numbers.popFront();
        hasData = true;
        firstInRow = false;
      }
    }

    if (!firstInRow) {
      std::cout << "\n";
      rowSums.pushBack(currentSum);
    }
  }

  if (rowSums.isEmpty()) {
    std::cout << "0\n";
  } else {
    bool firstSum = true;
    for (LIter< unsigned long long > sit = rowSums.begin(); sit != rowSums.end(); ++sit) {
      if (!firstSum) {
        std::cout << " ";
      }
      std::cout << *sit;
      firstSum = false;
    }
    std::cout << "\n";
  }

  return 0;
}
