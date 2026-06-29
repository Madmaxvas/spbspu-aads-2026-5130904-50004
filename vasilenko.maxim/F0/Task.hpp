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
  };

  inline bool operator==(const Task& lhs, const Task& rhs)
  {
    return lhs.id == rhs.id;
  }

  inline bool operator!=(const Task& lhs, const Task& rhs)
  {
    return !(lhs == rhs);
  }
}

#endif
