#include "Evaluator.hpp"

#include <stdexcept>
#include <limits>

#include "Stack.hpp"
#include "Queue.hpp"

long long vasilenko::safeAdd(long long a, long long b)
{
  if (b > 0 && a > std::numeric_limits< long long >::max() - b) {
    throw std::overflow_error("Overflow");
  }
  if (b < 0 && a < std::numeric_limits< long long >::min() - b) {
    throw std::underflow_error("Underflow");
  }
  return a + b;
}

long long vasilenko::safeSub(long long a, long long b)
{
  if (b < 0 && a > std::numeric_limits< long long >::max() + b) {
    throw std::overflow_error("Overflow");
  }
  if (b > 0 && a < std::numeric_limits< long long >::min() + b) {
    throw std::underflow_error("Underflow");
  }
  return a - b;
}

long long vasilenko::safeMul(long long a, long long b)
{
  if (a > 0 && b > 0 && a > std::numeric_limits< long long >::max() / b) {
    throw std::overflow_error("Overflow");
  }
  if (a > 0 && b < 0 && b < std::numeric_limits< long long >::min() / a) {
    throw std::underflow_error("Underflow");
  }
  if (a < 0 && b > 0 && a < std::numeric_limits< long long >::min() / b) {
    throw std::underflow_error("Underflow");
  }
  if (a < 0 && b < 0 && a < std::numeric_limits< long long >::max() / b) {
    throw std::overflow_error("Overflow");
  }
  return a * b;
}

long long vasilenko::safeDiv(long long a, long long b)
{
  if (b == 0) {
    throw std::invalid_argument("Division by zero");
  }
  if (a == std::numeric_limits< long long >::min() && b == -1) {
    throw std::overflow_error("Overflow");
  }
  return a / b;
}

long long vasilenko::safeMod(long long a, long long b)
{
  if (b == 0) {
    throw std::invalid_argument("Modulo by zero");
  }
  if (a == std::numeric_limits< long long >::min() && b == -1) {
    throw std::overflow_error("Overflow");
  }
  return a % b;
}

long long vasilenko::computePower(long long base, long long exponent)
{
  if (exponent < 0) {
    throw std::invalid_argument("Negative exponent is not supported");
  }
  if (exponent == 0) {
    return 1;
  }
  long long result = 1;
  for (long long i = 0; i < exponent; ++i) {
    result = safeMul(result, base);
  }
  return result;
}

bool vasilenko::isOperator(const std::string & token)
{
  return token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^";
}

int vasilenko::getPrecedence(const std::string & op)
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

bool vasilenko::isRightAssociative(const std::string & op)
{
  return op == "^";
}

vasilenko::Queue< std::string > vasilenko::convertToPostfix(const std::string & expression)
{
  Queue< std::string > outputQueue;
  Stack< std::string > operatorStack;
  size_t i = 0;

  while (i < expression.length()) {
    while (i < expression.length() && expression[i] == ' ') {
      i++;
    }
    if (i == expression.length()) {
      break;
    }

    size_t start = i;
    while (i < expression.length() && expression[i] != ' ') {
      i++;
    }
    std::string token = expression.substr(start, i - start);

    if (isOperator(token)) {
      while (!operatorStack.empty() && isOperator(operatorStack.top())) {
        const std::string topOp = operatorStack.top();
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
      while (!operatorStack.empty()) {
        const std::string topToken = operatorStack.top();
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

  while (!operatorStack.empty()) {
    const std::string topToken = operatorStack.top();
    operatorStack.pop();
    if (topToken == "(" || topToken == ")") {
      throw std::invalid_argument("Mismatched parentheses");
    }
    outputQueue.push(topToken);
  }
  return outputQueue;
}

long long vasilenko::evaluatePostfix(Queue< std::string > & postfixQueue)
{
  Stack< long long > evaluationStack;

  while (!postfixQueue.empty()) {
    const std::string token = postfixQueue.front();
    postfixQueue.pop();

    if (isOperator(token)) {
      if (evaluationStack.empty()) {
        throw std::invalid_argument("Invalid expression");
      }
      const long long rightOperand = evaluationStack.top();
      evaluationStack.pop();

      if (evaluationStack.empty()) {
        throw std::invalid_argument("Invalid expression");
      }
      const long long leftOperand = evaluationStack.top();
      evaluationStack.pop();

      long long result = 0;
      if (token == "+") {
        result = safeAdd(leftOperand, rightOperand);
      } else if (token == "-") {
        result = safeSub(leftOperand, rightOperand);
      } else if (token == "*") {
        result = safeMul(leftOperand, rightOperand);
      } else if (token == "/") {
        result = safeDiv(leftOperand, rightOperand);
      } else if (token == "%") {
        result = safeMod(leftOperand, rightOperand);
      } else if (token == "^") {
        result = computePower(leftOperand, rightOperand);
      }

      evaluationStack.push(result);
    } else {
      evaluationStack.push(std::stoll(token));
    }
  }

  if (evaluationStack.empty()) {
    throw std::invalid_argument("Empty expression");
  }
  const long long finalResult = evaluationStack.top();
  evaluationStack.pop();

  if (!evaluationStack.empty()) {
    throw std::invalid_argument("Invalid expression");
  }
  return finalResult;
}

long long vasilenko::evaluateExpression(const std::string & expression)
{
  Queue< std::string > postfix = convertToPostfix(expression);
  return evaluatePostfix(postfix);
}
