#include "System.hpp"
#include <iostream>
#include <string>

int main()
{
  vasilenko::System system;
  std::string command;

  while (std::cin >> command) {
    try {
      if (command == "add-loc") {
        std::string name;
        int minX = 0, minY = 0, maxX = 0, maxY = 0;
        if (!(std::cin >> name >> minX >> minY >> maxX >> maxY)) {
          std::cerr << "Invalid parameters for add-loc\n";
          return 1;
        }
        system.addLocation(name, minX, minY, maxX, maxY);
      } else if (command == "add-task") {
        std::string id;
        int x = 0, y = 0;
        if (!(std::cin >> id >> x >> y)) {
          std::cerr << "Invalid parameters for add-task\n";
          return 1;
        }
        system.addTask(id, x, y);
      } else if (command == "add-user") {
        std::string name;
        int startX = 0, startY = 0;
        if (!(std::cin >> name >> startX >> startY)) {
          std::cerr << "Invalid parameters for add-user\n";
          return 1;
        }
        system.addUser(name, startX, startY);
      } else if (command == "assign") {
        std::string userName, taskId;
        if (!(std::cin >> userName >> taskId)) {
          std::cerr << "Invalid parameters for assign\n";
          return 1;
        }
        system.assignTask(userName, taskId);
      } else if (command == "report-stat") {
        system.reportStat();
      } else if (command == "report-effort") {
        system.reportEffort();
      } else if (command == "predict") {
        std::string userName;
        if (!(std::cin >> userName)) {
          std::cerr << "Invalid parameters for predict\n";
          return 1;
        }
        system.predict(userName);
      } else {
        std::cerr << "Unknown command: " << command << "\n";
        return 1;
      }
    } catch (const std::exception& e) {
      std::cerr << "Internal error: " << e.what() << "\n";
      return 2;
    }
  }

  return 0;
}
