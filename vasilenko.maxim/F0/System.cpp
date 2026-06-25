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
    User* user = users_.find(userName);
    Task* task = tasks_.find(taskId);

    if (user == nullptr || task == nullptr || task->isDone) {
      return;
    }

    double dist = std::sqrt(std::pow(user->startX - task->x, 2) + std::pow(user->startY - task->y, 2));
    user->totalDistance += dist;
    user->startX = task->x;
    user->startY = task->y;
    user->completedCount++;
    task->isDone = true;
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
    User* user = const_cast<System*>(this)->users_.find(userName);
    if (user == nullptr || user->completedCount == 0) {
      std::cout << "Prediction for " << userName << ": N/A\n";
      return;
    }

    int remainingTasks = 0;
    for (const auto& task : tasks_) {
      if (!task.isDone) {
        remainingTasks++;
      }
    }

    double avgDist = user->totalDistance / user->completedCount;
    double prediction = avgDist * remainingTasks;
    std::cout << "Prediction for " << userName << ": " << std::fixed << std::setprecision(2) << prediction << "\n";
  }

}
