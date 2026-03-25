#include <cassert>

#include "Stack.hpp"
#include "Queue.hpp"
#include "Evaluator.hpp"

void testStack()
{
  vasilenko::Stack<int> stackObject;
  assert(stackObject.isEmpty());

  stackObject.push(10);
  stackObject.push(20);
  assert(!stackObject.isEmpty());
  assert(stackObject.getTop() == 20);

  stackObject.pop();
  assert(stackObject.getTop() == 10);

  stackObject.pop();
  assert(stackObject.isEmpty());
}

void testQueue()
{
  vasilenko::Queue<int> queueObject;
  assert(queueObject.isEmpty());

  queueObject.push(10);
  queueObject.push(20);
  assert(!queueObject.isEmpty());
  assert(queueObject.getFront() == 10);

  queueObject.pop();
  assert(queueObject.getFront() == 20);

  queueObject.pop();
  assert(queueObject.isEmpty());
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
