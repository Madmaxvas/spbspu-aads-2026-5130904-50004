#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Hash_Table.hpp"
#include "RTree.hpp"
#include "Task.hpp"
#include "User.hpp"

namespace vasilenko {

  class System {
  private:
    RTree rtree_;
    HashTable<std::string, Task> tasks_;
    HashTable<std::string, User> users_;

  public:
    void addLocation(const std::string& name, int minX, int minY, int maxX, int maxY);
    void addTask(const std::string& id, int x, int y);
    void addUser(const std::string& name, int startX, int startY);
    void assignTask(const std::string& userName, const std::string& taskId);
    void reportStat() const;
    void reportEffort() const;
    void predict(const std::string& userName) const;
  };

}

#endif
