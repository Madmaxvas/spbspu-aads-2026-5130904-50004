#include "BiList.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <utility>

int main()
{
  using namespace vasilenko_maxim;
  BiList< std::pair< std::string, BiList< unsigned long long > > > data;
  std::string name = "";

  while (std::cin >> name)
  {
    BiList< unsigned long long > nums;
    unsigned long long val = 0;
    while (std::cin >> val)
    {
      nums.push_back(val);
    }
    data.push_back(std::make_pair(name, std::move(nums)));
    if (!std::cin.eof())
    {
      std::cin.clear();
    }
  }

  if (data.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  for (auto it = data.begin(); it != data.end(); )
  {
    std::cout << it->first;
    if (++it != data.end())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  BiList< unsigned long long > sums;
  bool processing = true;
  size_t index = 0;

  while (processing)
  {
    processing = false;
    unsigned long long current_sum = 0;
    bool first_in_row = true;
    bool row_has_data = false;

    for (auto it = data.begin(); it != data.end(); ++it)
    {
      if (index < it->second.size())
      {
        auto inner_it = it->second.begin();
        for (size_t i = 0; i < index; ++i)
        {
          ++inner_it;
        }

        if (!first_in_row)
        {
          std::cout << " ";
        }
        std::cout << *inner_it;

        if (row_has_data && (std::numeric_limits< unsigned long long >::max() - current_sum < *inner_it))
        {
          std::cerr << "Overflow\n";
          return 1;
        }
        current_sum += *inner_it;
        row_has_data = true;
        first_in_row = false;
      }
      if (index + 1 < it->second.size())
      {
        processing = true;
      }
    }

    if (row_has_data)
    {
      std::cout << "\n";
      sums.push_back(current_sum);
    }
    index++;
  }

  for (auto it = sums.begin(); it != sums.end(); )
  {
    std::cout << *it;
    if (++it != sums.end())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  return 0;
}
