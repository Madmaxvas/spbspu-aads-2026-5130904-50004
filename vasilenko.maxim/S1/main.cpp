#include <iostream>
#include <string>
#include <limits>
#include <cstddef>
#include <algorithm>
#include "list.hpp"

struct NamedList
{
  std::string name;
  vasilenko_maxim::Bilist< unsigned long long > numbers;
};

int main()
{
  using namespace vasilenko_maxim;
  Bilist< NamedList > allSeqs;
  std::string name;

  while (std::cin >> name)
  {
    NamedList current;
    current.name = name;
    while (std::cin.peek() != '\n' && std::cin.peek() != EOF)
    {
      unsigned long long val = 0;
      if (std::cin >> val)
      {
        current.numbers.pushBack(val);
      }
      else
      {
        std::cin.clear();
        if (std::cin.peek() != EOF) std::cin.ignore();
      }
    }
    allSeqs.pushBack(current);
  }

  if (allSeqs.isEmpty())
  {
    std::cout << "0\n";
    return 0;
  }

  for (auto it = allSeqs.begin(); it != allSeqs.end(); )
  {
    std::cout << it->name;
    if (++it != allSeqs.end()) std::cout << " ";
  }
  std::cout << "\n";

  Bilist< unsigned long long > sums;
  bool hasData = true;
  while (hasData)
  {
    hasData = false;
    unsigned long long currentSum = 0;
    bool firstInRow = true;
    bool rowEmpty = true;

    for (auto it = allSeqs.begin(); it != allSeqs.end(); ++it)
    {
      if (!it->numbers.isEmpty())
      {
        unsigned long long val = it->numbers.front();
        if (!firstInRow) std::cout << " ";
        std::cout << val;

        if (std::numeric_limits< unsigned long long >::max() - currentSum < val)
        {
          std::cerr << "Overflow error\n";
          return 1;
        }
        currentSum += val;
        it->numbers.popFront();
        rowEmpty = false;
        firstInRow = false;
      }
      if (!it->numbers.isEmpty()) hasData = true;
    }

    if (!rowEmpty)
    {
      std::cout << "\n";
      sums.pushBack(currentSum);
    }
  }

  for (auto it = sums.begin(); it != sums.end(); )
  {
    std::cout << *it;
    if (++it != sums.end()) std::cout << " ";
  }
  std::cout << "\n";

  return 0;
}
