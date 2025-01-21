#include "stack.h"

#define EXPRESSIONS   3     // total no of expression to convert
#define EXPR_LENGTH   30    // max length of expression


/* verify if the oper1 has higher precedence that oper2 */
bool is_precedence(char oper1, char oper2) {
  switch (oper1) {
    case '+':
    case '-':
      return (oper2 == '+' || oper2 == '-');
    case '*':
    case '/':
    case '%':
      return true;
    default:
      return false;
  }
}


bool is_operator(char oper) {
  return (oper == '+' || oper == '-' || oper == '*' || oper == '/' || oper == '%');
}


char* infix_to_postfix(char *expr) {
  stack *oper = stack_init();   // stack to hold the operators
  int p = 0;                    // index counter for postfix sting

  // allocate memory for string which holds the result (postfix expression)
  char *postfix = malloc(EXPR_LENGTH * sizeof(char));

  for (int i = 0; i < strlen(expr); i++) {
    // if it's an operand, then add it to output string
    if ( !is_operator(expr[i]) ) {
      postfix[p++] = expr[i];
      continue;
    }

    while (!is_stack_empty(oper) && is_precedence(stack_peek(oper)->element.cval, expr[i])) {
      char top_symbol = stack_pop(oper)->element.cval;
      postfix[p++] = top_symbol;
    }

    char operator = expr[i];
    stack_push(oper, &operator, CHAR);
  }

  // finally add the left over operations from stack into postfix string
  while (!is_stack_empty(oper)) {
    postfix[p++] = stack_pop(oper)->element.cval;
  }

  // adding NULL character to mark the end of string
  postfix[p] = '\0';

  return postfix;
}






/* EVERY THING STARTS HERE */
int main() {
  char expressions[EXPRESSIONS][EXPR_LENGTH] = {
    "A+B",
    "A+B-C",
    "A*B+C*D"
  };

  for (int idx = 0; idx < EXPRESSIONS; idx++)
    printf("%s = %s \n", expressions[idx], infix_to_postfix(expressions[idx]) );

  return 0;
}