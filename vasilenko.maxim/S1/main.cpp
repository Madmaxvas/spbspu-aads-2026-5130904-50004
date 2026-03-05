#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <limits>
#include "list.hpp"

struct NamedList
{
  std::string name;
  vasilenko_maxim::List< long long > numbers;
};

int main()
{
  using namespace vasilenko_maxim;
  List< NamedList > allSeqs;
  std::string line;

  while (std::getline(std::cin, line))
  {
    if (line.empty())
    {
      continue;
    }
    std::stringstream ss(line);
    std::string listName;
    if (!(ss >> listName))
    {
      continue;
    }

    NamedList current;
    current.name = listName;
    std::string valStr;
    try
    {
      while (ss >> valStr)
      {
        current.numbers.pushBack(std::stoll(valStr));
      }
    }
    catch (const std::out_of_range &)
    {
      std::cerr << "Error: constant too large\n";
      return 1;
    }
    catch (const std::invalid_argument &)
    {
      std::cerr << "Error: invalid input\n";
      return 1;
    }
    allSeqs.pushBack(current);
  }

  if (allSeqs.isEmpty())
  {
    std::cout << "0\n";
    return 0;
  }

  for (LIter< NamedList > it = allSeqs.begin(); it != allSeqs.end(); ++it)
  {
    std::cout << it->name << (it != allSeqs.end() ? " " : "");
  }
  std::cout << "\n";

  List< long long > rowSums;
  bool hasData = true;
  while (hasData)
  {
    hasData = false;
    long long currentSum = 0;
    bool firstInRow = true;

    for (LIter< NamedList > it = allSeqs.begin(); it != allSeqs.end(); ++it)
    {
      if (!it->numbers.isEmpty())
      {
        if (!firstInRow)
        {
          std::cout << " ";
        }
        long long val = it->numbers.front();
        std::cout << val;

        currentSum += val;
        it->numbers.popFront();
        hasData = true;
        firstInRow = false;
      }
    }

    if (!firstInRow)
    {
      std::cout << "\n";
      rowSums.pushBack(currentSum);
    }
  }

  for (LIter< long long > sit = rowSums.begin(); sit != rowSums.end(); ++sit)
  {
    std::cout << *sit << (sit != rowSums.end() ? " " : "");
  }
  std::cout << "\n";

  return 0;
}
