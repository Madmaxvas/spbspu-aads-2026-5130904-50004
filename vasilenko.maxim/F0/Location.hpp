#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>

namespace vasilenko {

  struct Location {
    std::string name;
    int minX;
    int minY;
    int maxX;
    int maxY;
    int totalTasksCount;

    bool operator==(const Location& other) const
    {
      return name == other.name && minX == other.minX && minY == other.minY &&
             maxX == other.maxX && maxY == other.maxY && totalTasksCount == other.totalTasksCount;
    }

    bool operator!=(const Location& other) const
    {
      return !(*this == other);
    }
  };

}

#endif
