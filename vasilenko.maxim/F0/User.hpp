#ifndef USER_HPP
#define USER_HPP

#include <string>

namespace vasilenko {
  struct User {
    std::string name;
    int startX;
    int startY;
    double totalDistance;
    int completedCount;
  };

  inline bool operator==(const User& lhs, const User& rhs)
  {
    return lhs.name == rhs.name;
  }

  inline bool operator!=(const User& lhs, const User& rhs)
  {
    return !(lhs == rhs);
  }
}

#endif
