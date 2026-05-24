#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "commands.hpp"

int main(int argc, char* argv[])
{
  const int successCode = 0;
  const int errorCode = 1;

  if (argc < 2) {
    std::cerr << "Usage: ./lab <filename>\n";
    return errorCode;
  }

  vasilenko::DictMap dicts;
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file.\n";
    return errorCode;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream iss(line);
    std::string dictName;
    int key = 0;
    std::string value;

    iss >> dictName;
    while (iss >> key >> value) {
      dicts[dictName].push(key, value);
    }
  }

  using CommandFunc = std::function<void(std::istringstream&, vasilenko::DictMap&)>;
  std::map<std::string, CommandFunc> commands;

  commands["print"] = [](std::istringstream& iss, vasilenko::DictMap& d) -> void
  {
    std::string dictName;
    if (iss >> dictName) {
      vasilenko::processPrint(dictName, d);
    } else {
      std::cout << "<INVALID COMMAND>\n";
    }
  };

  commands["union"] = [](std::istringstream& iss, vasilenko::DictMap& d) -> void
  {
    std::string target;
    std::string left;
    std::string right;
    if (iss >> target >> left >> right) {
      vasilenko::processUnion(target, left, right, d);
    } else {
      std::cout << "<INVALID COMMAND>\n";
    }
  };

  commands["intersect"] = [](std::istringstream& iss, vasilenko::DictMap& d) -> void
  {
    std::string target;
    std::string left;
    std::string right;
    if (iss >> target >> left >> right) {
      vasilenko::processIntersect(target, left, right, d);
    } else {
      std::cout << "<INVALID COMMAND>\n";
    }
  };

  commands["complement"] = [](std::istringstream& iss, vasilenko::DictMap& d) -> void
  {
    std::string target;
    std::string left;
    std::string right;
    if (iss >> target >> left >> right) {
      vasilenko::processComplement(target, left, right, d);
    } else {
      std::cout << "<INVALID COMMAND>\n";
    }
  };

  std::string commandLine;
  while (std::getline(std::cin, commandLine)) {
    if (commandLine.empty()) {
      continue;
    }
    std::istringstream iss(commandLine);
    std::string cmd;
    iss >> cmd;
    auto cmdIt = commands.find(cmd);
    if (cmdIt != commands.end()) {
      cmdIt->second(iss, dicts);
    } else {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  return successCode;
}
