#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include <string>
#include "Queue.hpp"

namespace vasilenko {

  long long safeAdd(long long a, long long b);
  long long safeSub(long long a, long long b);
  long long safeMul(long long a, long long b);
  long long safeDiv(long long a, long long b);
  long long safeMod(long long a, long long b);
  long long computePower(long long base, long long exponent);

  bool isOperator(const std::string & token);
  int getPrecedence(const std::string & op);
  bool isRightAssociative(const std::string & op);

  Queue< std::string > convertToPostfix(const std::string & expression);
  long long evaluatePostfix(Queue< std::string > & postfixQueue);
  long long evaluateExpression(const std::string & expression);

}

#endif
