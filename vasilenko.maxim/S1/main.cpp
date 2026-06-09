#include "BiList.hpp"
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <sstream>
#include <stdexcept>

namespace
{
  unsigned long long safeAdd(unsigned long long a, unsigned long long b)
  {
    unsigned long long maxVal = std::numeric_limits< unsigned long long >::max();
    if (maxVal - a < b)
    {
      throw std::overflow_error("Overflow");
    }
    return a + b;
  }
}

int main()
{
  using SeqType = vasilenko_maxim::BiList< unsigned long long >;
  using EntryType = std::pair< std::string, SeqType >;
  using ListType = vasilenko_maxim::BiList< EntryType >;

  ListType data;
  std::string line;

  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);
    std::string name;
    if (iss >> name)
    {
      SeqType seq;
      unsigned long long val = 0;
      while (iss >> val)
      {
        seq.pushBack(val);
      }
      data.pushBack(std::make_pair(name, std::move(seq)));
    }
  }

  if (data.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  auto itData = data.begin();
  std::cout << itData->first;
  ++itData;
  for (; itData != data.end(); ++itData)
  {
    std::cout << " " << itData->first;
  }
  std::cout << "\n";

  using ValueIter = vasilenko_maxim::LIter< unsigned long long >;
  using IterPair = std::pair< ValueIter, ValueIter >;
  vasilenko_maxim::BiList< IterPair > trackers;

  for (auto it = data.begin(); it != data.end(); ++it)
  {
    trackers.pushBack(std::make_pair(it->second.begin(), it->second.end()));
  }

  SeqType sums;

  while (true)
  {
    auto it = trackers.begin();
    while (it != trackers.end() && it->first == it->second)
    {
      ++it;
    }

    if (it == trackers.end())
    {
      break;
    }

    unsigned long long currentSum = 0;
    try
    {
      unsigned long long val = *(it->first);
      std::cout << val;
      currentSum = val;
      ++(it->first);
      ++it;

      for (; it != trackers.end(); ++it)
      {
        if (it->first != it->second)
        {
          val = *(it->first);
          std::cout << " " << val;
          currentSum = safeAdd(currentSum, val);
          ++(it->first);
        }
      }
    }
    catch (const std::overflow_error& e)
    {
      std::cout << "\n";
      std::cerr << "Overflow\n";
      return 1;
    }

    std::cout << "\n";
    sums.pushBack(currentSum);
  }

  if (sums.empty())
  {
    std::cout << "0\n";
  }
  else
  {
    auto itSums = sums.begin();
    std::cout << *itSums;
    ++itSums;
    for (; itSums != sums.end(); ++itSums)
    {
      std::cout << " " << *itSums;
    }
    std::cout << "\n";
  }

  return 0;
}
