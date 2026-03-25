#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP
#include <string>
#include <sstream>
#include "Stack.hpp"
#include "Queue.hpp"

namespace vasilenko {
  bool isOperator(const std::string& t) { return t=="+"||t=="-"||t=="*"||t=="/"||t=="%"||t=="^"; }
  int getPrecedence(const std::string& op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/" || op == "%") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
  }
  bool isRightAssociative(const std::string& op) { return op == "^"; }

  Queue<std::string> convertToPostfix(const std::string& expr)
  {
    Queue<std::string> out;
    Stack<std::string> ops;
    std::istringstream stream(expr);
    std::string t;
    while (stream >> t) {
      if (isOperator(t)) {
        while (!ops.isEmpty() && isOperator(ops.getTop())) {
          if (getPrecedence(ops.getTop()) > getPrecedence(t) ||
             (getPrecedence(ops.getTop()) == getPrecedence(t) && !isRightAssociative(t))) {
            out.push(ops.getTop()); ops.pop();
          } else break;
        }
        ops.push(t);
      } else if (t == "(") ops.push(t);
      else if (t == ")") {
        while (!ops.isEmpty() && ops.getTop() != "(") { out.push(ops.getTop()); ops.pop(); }
        ops.pop();
      } else out.push(t);
    }
    while (!ops.isEmpty()) { out.push(ops.getTop()); ops.pop(); }
    return out;
  }
}
#endif
