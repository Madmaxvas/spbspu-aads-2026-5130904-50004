#include <cassert>

#include "Stack.hpp"
#include "Queue.hpp"
#include "Evaluator.hpp"

void testStack()
{
  vasilenko::Stack< int > stackObject;
  assert(stackObject.empty());

  stackObject.push(10);
  stackObject.push(20);
  assert(!stackObject.empty());
  assert(stackObject.top() == 20);

  stackObject.pop();
  assert(stackObject.top() == 10);

  stackObject.pop();
  assert(stackObject.empty());
}

void testQueue()
{
  vasilenko::Queue< int > queueObject;
  assert(queueObject.empty());

  queueObject.push(10);
  queueObject.push(20);
  assert(!queueObject.empty());
  assert(queueObject.front() == 10);

  queueObject.pop();
  assert(queueObject.front() == 20);

  queueObject.pop();
  assert(queueObject.empty());
}

void testExponentiation()
{
  assert(vasilenko::evaluateExpression("2 ^ 3") == 8);
  assert(vasilenko::evaluateExpression("2 ^ 3 ^ 2") == 512);
  assert(vasilenko::evaluateExpression("2 + 3 ^ 2") == 11);
  assert(vasilenko::evaluateExpression("( 2 + 3 ) ^ 2") == 25);
}

int main()
{
  testStack();
  testQueue();
  testExponentiation();
  return 0;
}
