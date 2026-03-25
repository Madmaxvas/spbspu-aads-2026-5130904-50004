#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include <string>
#include <sstream>
#include <stdexcept>

#include "Stack.hpp"
#include "Queue.hpp"

namespace vasilenko {

  long long computePower(long long base, long long exponent)
  {
    if (exponent < 0) {
      throw std::invalid_argument("Negative exponent is not supported");
    }
    long long result = 1;
    for (long long i = 0; i < exponent; ++i) {
      result *= base;
    }
    return result;
  }

  bool isOperator(const std::string& token)
  {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^";
  }

  int getPrecedence(const std::string& op)
  {
    if (op == "^") {
      return 3;
    }
    if (op == "*" || op == "/" || op == "%") {
      return 2;
    }
    if (op == "+" || op == "-") {
      return 1;
    }
    return 0;
  }

  bool isRightAssociative(const std::string& op)
  {
    return op == "^";
  }

  Queue<std::string> convertToPostfix(const std::string& expression)
  {
    Queue<std::string> outputQueue;
    Stack<std::string> operatorStack;
    std::istringstream stream(expression);
    std::string token;

    while (stream >> token) {
      if (isOperator(token)) {
        while (!operatorStack.isEmpty() && isOperator(operatorStack.getTop())) {
          const std::string topOp = operatorStack.getTop();
          const int tokenPrec = getPrecedence(token);
          const int topPrec = getPrecedence(topOp);

          if (topPrec > tokenPrec || (topPrec == tokenPrec && !isRightAssociative(token))) {
            outputQueue.push(topOp);
            operatorStack.pop();
          } else {
            break;
          }
        }
        operatorStack.push(token);
      } else if (token == "(") {
        operatorStack.push(token);
      } else if (token == ")") {
        bool foundLeftParen = false;
        while (!operatorStack.isEmpty()) {
          const std::string topToken = operatorStack.getTop();
          operatorStack.pop();
          if (topToken == "(") {
            foundLeftParen = true;
            break;
          }
          outputQueue.push(topToken);
        }
        if (!foundLeftParen) {
          throw std::invalid_argument("Mismatched parentheses");
        }
      } else {
        outputQueue.push(token);
      }
    }

    while (!operatorStack.isEmpty()) {
      const std::string topToken = operatorStack.getTop();
      operatorStack.pop();
      if (topToken == "(" || topToken == ")") {
        throw std::invalid_argument("Mismatched parentheses");
      }
      outputQueue.push(topToken);
    }
    return outputQueue;
  }

  long long evaluatePostfix(Queue<std::string>& postfixQueue)
  {
    Stack<long long> evaluationStack;

    while (!postfixQueue.isEmpty()) {
      const std::string token = postfixQueue.getFront();
      postfixQueue.pop();

      if (isOperator(token)) {
        if (evaluationStack.isEmpty()) {
          throw std::invalid_argument("Invalid expression");
        }
        const long long rightOperand = evaluationStack.getTop();
        evaluationStack.pop();

        if (evaluationStack.isEmpty()) {
          throw std::invalid_argument("Invalid expression");
        }
        const long long leftOperand = evaluationStack.getTop();
        evaluationStack.pop();

        long long result = 0;
        if (token == "+") {
          result = leftOperand + rightOperand;
        } else if (token == "-") {
          result = leftOperand - rightOperand;
        } else if (token == "*") {
          result = leftOperand * rightOperand;
        } else if (token == "/") {
          result = leftOperand / rightOperand;
        } else if (token == "%") {
          result = leftOperand % rightOperand;
        } else if (token == "^") {
          result = computePower(leftOperand, rightOperand);
        }

        evaluationStack.push(result);
      } else {
        evaluationStack.push(std::stoll(token));
      }
    }

    if (evaluationStack.isEmpty()) {
      throw std::invalid_argument("Empty expression");
    }
    const long long finalResult = evaluationStack.getTop();
    evaluationStack.pop();

    if (!evaluationStack.isEmpty()) {
      throw std::invalid_argument("Invalid expression");
    }
    return finalResult;
  }

  long long evaluateExpression(const std::string& expression)
  {
    Queue<std::string> postfix = convertToPostfix(expression);
    return evaluatePostfix(postfix);
  }

}

#endif
