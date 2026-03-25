#include <cassert>
#include "Stack.hpp"
#include "Queue.hpp"
#include "Evaluator.hpp"

void testLogic()
{
  assert(vasilenko::evaluateExpression("2 ^ 3") == 8);
  assert(vasilenko::evaluateExpression("2 ^ 3 ^ 2") == 512);
  assert(vasilenko::evaluateExpression("( 2 + 3 ) * 4") == 20);
}

int main()
{
  vasilenko::Stack<int> s;
  s.push(1);
  assert(s.getTop() == 1);

  testLogic();
  return 0;
}
