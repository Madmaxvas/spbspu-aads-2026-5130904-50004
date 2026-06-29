#include "System.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

namespace vasilenko {
  void System::addLocation(const std::string& name, int minX, int minY, int maxX, int maxY)
  {
    Location loc{name, minX, minY, maxX, maxY, 0};
    rtree_.insert(loc);
  }

  void System::addTask(const std::string& id, int x, int y)
  {
    Task task{id, x, y, false, {}};
    Vector<Location*> intersections = rtree_.findIntersections(x, y);
    for (std::size_t i = 0; i < intersections.size(); ++i) {
      task.parentLocations.push_back(intersections[i]->name);
      intersections[i]->totalTasksCount++;
    }
    tasks_.insert(id, task);
  }

  void System::addUser(const std::string& name, int startX, int startY)
  {
    User user{name, startX, startY, 0.0, 0};
    users_.insert(name, user);
  }

  void System::assignTask(const std::string& userName, const std::string& taskId)
  {
    auto userIt = users_.find(userName);
    auto taskIt = tasks_.find(taskId);

    if (userIt == users_.end() || taskIt == tasks_.end() || taskIt->isDone) {
      return;
    }

    double dist = std::sqrt(std::pow(userIt->startX - taskIt->x, 2) + std::pow(userIt->startY - taskIt->y, 2));
    userIt->totalDistance += dist;
    userIt->startX = taskIt->x;
    userIt->startY = taskIt->y;
    userIt->completedCount++;
    taskIt->isDone = true;
  }

  void System::reportStat() const
  {
    std::cout << "User | Location | Done | Total | Contribution %\n";
    for (const auto& user : users_) {
      std::cout << user.name << " | ... \n";
    }
  }

  void System::reportEffort() const
  {
    std::cout << "Effort Report:\n";
    for (const auto& user : users_) {
      std::cout << user.name << ": " << user.totalDistance << "\n";
    }
  }

  void System::predict(const std::string& userName) const
  {
    auto userIt = const_cast<System*>(this)->users_.find(userName);
    if (userIt == const_cast<System*>(this)->users_.end() || userIt->completedCount == 0) {
      std::cout << "Prediction for " << userName << ": N/A\n";
      return;
    }

    int remainingTasks = 0;
    for (const auto& task : tasks_) {
      if (!task.isDone) {
        remainingTasks++;
      }
    }

    double avgDist = userIt->totalDistance / userIt->completedCount;
    double prediction = avgDist * remainingTasks;
    std::cout << "Prediction for " << userName << ": " << std::fixed << std::setprecision(2) << prediction << "\n";
  }
}
