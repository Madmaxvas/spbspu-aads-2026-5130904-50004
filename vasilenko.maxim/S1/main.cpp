#include "BiList.hpp"
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <stdexcept>
#include <cctype>

namespace vasilenko
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
  using SeqType = vasilenko::BiList< unsigned long long >;

  struct EntryType
  {
    std::string name;
    SeqType seq;
  };

  using ListType = vasilenko::BiList< EntryType >;

  ListType data;
  std::string name;

  while (std::cin >> name)
  {
    SeqType seq;
    while (true)
    {
      int c = std::cin.get();
      if (c == '\n' || c == std::char_traits< char >::eof())
      {
        break;
      }

      if (std::isdigit(c))
      {
        unsigned long long val = c - '0';
        while (true)
        {
          c = std::cin.get();
          if (c != std::char_traits< char >::eof() && std::isdigit(c))
          {
            val = val * 10 + (c - '0');
          }
          else
          {
            break;
          }
        }
        seq.pushBack(val);

        if (c == '\n' || c == std::char_traits< char >::eof())
        {
          break;
        }
      }
    }

    EntryType entry;
    entry.name = name;
    entry.seq = std::move(seq);
    data.pushBack(std::move(entry));
  }

  if (data.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  auto itData = data.begin();
  std::cout << itData->name;
  ++itData;
  for (; itData != data.end(); ++itData)
  {
    std::cout << " " << itData->name;
  }
  std::cout << "\n";

  using ValueIter = vasilenko::LIter< unsigned long long >;

  struct Tracker
  {
    ValueIter current;
    ValueIter end;
  };

  vasilenko::BiList< Tracker > trackers;

  for (auto it = data.begin(); it != data.end(); ++it)
  {
    Tracker tr;
    tr.current = it->seq.begin();
    tr.end = it->seq.end();
    trackers.pushBack(tr);
  }

  SeqType sums;

  while (true)
  {
    auto it = trackers.begin();
    while (it != trackers.end() && it->current == it->end)
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
      unsigned long long val = *(it->current);
      std::cout << val;
      currentSum = val;
      ++(it->current);
      ++it;

      for (; it != trackers.end(); ++it)
      {
        if (it->current != it->end)
        {
          val = *(it->current);
          std::cout << " " << val;
          currentSum = vasilenko::safeAdd(currentSum, val);
          ++(it->current);
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
