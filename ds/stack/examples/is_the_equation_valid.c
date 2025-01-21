#include "stack.h"

#define EXPR_CNT  6


bool is_expression_valid(char *expr) {
  stack *s = stack_init();

  for (int i = 0; i < strlen(expr); i++) {
    // if it's a opening type, then add it to the stack
    if (expr[i] == '{' || expr[i] == '(' || expr[i] == '[') {
      stack_push(s, &expr[i], CHAR);
      continue;
    }
    
    // if it's a closing type, then pop the last element
    // check if the element is a opening of the closing type
    if (expr[i] == '}' || expr[i] == ')' || expr[i] == ']') {
      // pop the element from the stack
      stack_element *se = stack_pop(s);

      if (expr[i] == '}' && se->element.cval != '{') return false;
      else if (expr[i] == ')' && se->element.cval != '(') return false;
      else if (expr[i] == ']' && se->element.cval != '[') return false;
    }
  }

  // if stack is empty, then for every opening type there is a closing type
  // if not then the equation is not valid
  if (!is_stack_empty(s)) return false;

  return true;
}








// Universe starts here
int main() {
  // Check if these expressions are Valid or not.
  // If these are valid, then all opening type has corresponding type

  char expr[EXPR_CNT][100] = {
    "7 - ((X * ((X + Y) / (J - 3)) + Y) / (4 - 2.5))",
    "{ x + (y - [a + b]) * c - [(d + e)]} / (h - (j - (k - [l - n])))",
    "(((A)))",
    "((H) * {([J + K])})",
    "(A + B) - {C + D} - [F + G]",
    "{[A + B] - [(C - D)]"
  };

  for (int exp_id = 0; exp_id < EXPR_CNT; exp_id++) {
    printf(
      "Expression: %s is valid? --> %s\n", 
      expr[exp_id], 
      is_expression_valid(expr[exp_id]) ? "True" : "False"
    );
  }

  return 0;
}