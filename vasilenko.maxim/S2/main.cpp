X#include <iostream>
#include <fstream>
#include "Stack.hpp"
#include "Evaluator.hpp"

int main(int argc, char* argv[])
{
  std::istream* input = &std::cin;
  std::ifstream file;
  if (argc == 2) {
    file.open(argv[1]);
    input = &file;
  }
  vasilenko::Stack<long long> res;
  std::string line;
  try {
    while (std::getline(*input, line)) {
      if (!line.empty()) res.push(vasilenko::evaluateExpression(line));
    }
    while (!res.isEmpty()) {
      std::cout << res.getTop() << (res.isEmpty() ? "" : " ");
      res.pop();
    }
    std::cout << "\n";
  } catch (...) {
    return 2;
  }
  return 0;
}
