#include <iostream>
#include <fstream>
#include <string>

#include "Stack.hpp"
#include "Evaluator.hpp"

int main(int argc, char* argv[])
{
  if (argc > 2) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  std::istream* inputStream = &std::cin;
  std::ifstream fileStream;

  if (argc == 2) {
    fileStream.open(argv[1]);
    if (!fileStream.is_open()) {
      std::cerr << "Failed to open file\n";
      return 1;
    }
    inputStream = &fileStream;
  }

  vasilenko::Stack<long long> finalResults;
  std::string line;

  try {
    while (std::getline(*inputStream, line)) {
      if (line.empty()) {
        continue;
      }

      const long long result = vasilenko::evaluateExpression(line);
      finalResults.push(result);
    }

    bool isFirst = true;
    while (!finalResults.isEmpty()) {
      if (!isFirst) {
        std::cout << " ";
      }
      std::cout << finalResults.getTop();
      finalResults.pop();
      isFirst = false;
    }
    std::cout << "\n";

  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 2;
  }

  return 0;
}
