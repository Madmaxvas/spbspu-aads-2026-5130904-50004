#ifndef TASK_HPP
#define TASK_HPP

#include "Vector.hpp"
#include <string>

namespace vasilenko {

  struct Task {
    std::string id;
    int x;
    int y;
    bool isDone;
    Vector<std::string> parentLocations;

    bool operator==(const Task& other) const
    {
      return id == other.id;
    }

    bool operator!=(const Task& other) const
    {
      return !(*this == other);
    }
  };

}

#endif
