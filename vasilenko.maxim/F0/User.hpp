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

    bool operator==(const User& other) const
    {
      return name == other.name;
    }

    bool operator!=(const User& other) const
    {
      return !(*this == other);
    }
  };

}

#endif
