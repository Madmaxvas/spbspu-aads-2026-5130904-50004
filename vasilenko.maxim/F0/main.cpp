#include "System.hpp"
#include <functional>
#include <iostream>
#include <string>

int main()
{
  vasilenko::System system;
  vasilenko::HashTable<std::string, std::function<void()>> commands;

  commands.insert("add-loc", [&system]() {
    std::string name;
    int minX = 0, minY = 0, maxX = 0, maxY = 0;
    if (!(std::cin >> name >> minX >> minY >> maxX >> maxY)) {
      throw std::invalid_argument("Invalid parameters for add-loc");
    }
    system.addLocation(name, minX, minY, maxX, maxY);
  });

  commands.insert("add-task", [&system]() {
    std::string id;
    int x = 0, y = 0;
    if (!(std::cin >> id >> x >> y)) {
      throw std::invalid_argument("Invalid parameters for add-task");
    }
    system.addTask(id, x, y);
  });

  commands.insert("add-user", [&system]() {
    std::string name;
    int startX = 0, startY = 0;
    if (!(std::cin >> name >> startX >> startY)) {
      throw std::invalid_argument("Invalid parameters for add-user");
    }
    system.addUser(name, startX, startY);
  });

  commands.insert("assign", [&system]() {
    std::string userName, taskId;
    if (!(std::cin >> userName >> taskId)) {
      throw std::invalid_argument("Invalid parameters for assign");
    }
    system.assignTask(userName, taskId);
  });

  commands.insert("report-stat", [&system]() {
    system.reportStat();
  });

  commands.insert("report-effort", [&system]() {
    system.reportEffort();
  });

  commands.insert("predict", [&system]() {
    std::string userName;
    if (!(std::cin >> userName)) {
      throw std::invalid_argument("Invalid parameters for predict");
    }
    system.predict(userName);
  });

  std::string command;
  while (std::cin >> command) {
    try {
      auto it = commands.find(command);
      if (it != commands.end()) {
        (*it)();
      } else {
        std::cerr << "Unknown command: " << command << "\n";
        return 1;
      }
    } catch (const std::invalid_argument& e) {
      std::cerr << e.what() << "\n";
      return 1;
    } catch (const std::exception& e) {
      std::cerr << "Internal error: " << e.what() << "\n";
      return 2;
    }
  }
  return 0;
}
