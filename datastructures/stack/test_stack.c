#include <assert.h>

#include "stack.h"


int main() {
  // Test 1: Initialize the stack
  stack *myStack = stack_init();
  assert(myStack != NULL);
  printf("Test 1 Passed: Stack initialized successfully.\n");

  // Test 2: Check if the stack is empty
  assert(is_stack_empty(myStack) == true);
  printf("Test 2 Passed: Stack is empty.\n");

  // Test 3: Push elements onto the stack
  int intValue = 42;
  assert(stack_push(myStack, &intValue, INT) == true);
  printf("Test 3.1 Passed: Integer pushed onto stack.\n");

  double floatValue = 3.14;
  assert(stack_push(myStack, &floatValue, FLOAT) == true);
  printf("Test 3.2 Passed: Float pushed onto stack.\n");

  char charValue = 'A';
  assert(stack_push(myStack, &charValue, CHAR) == true);
  printf("Test 3.3 Passed: Char pushed onto stack.\n");

  char *stringValue = "Hello, Stack!";
  assert(stack_push(myStack, stringValue, STRING) == true);
  printf("Test 3.4 Passed: String pushed onto stack.\n");

  // Test 4: Check if the stack is full
  assert(is_stack_full(myStack) == false);
  printf("Test 4 Passed: Stack is not full.\n");

  // Test 5: Peek at the top element
  const stack_element *topElement = stack_peek(myStack);
  assert(topElement != NULL);
  assert(topElement->etype == STRING);
  printf("Test 5 Passed: Peeked at top element: %s\n", topElement->element.sval);

  // Test 6: Pop elements from the stack
  stack_element *poppedElement;

  // Pop string
  poppedElement = stack_pop(myStack);
  assert(poppedElement != NULL);
  assert(poppedElement->etype == STRING);
  printf("Test 6.1 Passed: Popped element (string): %s\n", poppedElement->element.sval);
  free(poppedElement->element.sval); // Free the string
  free(poppedElement); // Free the stack_element

  // Pop char
  poppedElement = stack_pop(myStack);
  assert(poppedElement != NULL);
  assert(poppedElement->etype == CHAR);
  printf("Test 6.2 Passed: Popped element (char): %c\n", poppedElement->element.cval);
  free(poppedElement); // Free the stack_element

  // Pop float
  poppedElement = stack_pop(myStack);
  assert(poppedElement != NULL);
  assert(poppedElement->etype == FLOAT);
  printf("Test 6.3 Passed: Popped element (float): %f\n", poppedElement->element.dval);
  free(poppedElement); // Free the stack_element

  // Pop integer
  poppedElement = stack_pop(myStack);
  assert(poppedElement != NULL);
  assert(poppedElement->etype == INT);
  printf("Test 6.4 Passed: Popped element (int): %d\n", poppedElement->element.ival);
  free(poppedElement); // Free the stack_element

  // Test 7: Check if the stack is empty after popping all elements
  assert(is_stack_empty(myStack) == true);
  printf("Test 7 Passed: Stack is empty after popping all elements.\n");

  // Test 8: Free the stack
  stack_cleanup(myStack);
  printf("Test 8 Passed: Stack freed successfully.\n");

  return 0;
}