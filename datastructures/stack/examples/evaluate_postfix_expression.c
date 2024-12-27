#include <math.h>

#include "stack.h"

#define EXPRESSIONS   2
#define EXPR_LENGTH   80



double evaluate(char operator, double operand1, double operand2) {
  switch(operator) {
    case '+': return (operand1 + operand2);
    case '-': return (operand1 - operand2);
    case '*': return (operand1 * operand2);
    case '/': return (operand1 / operand2);
    case '$': return pow(operand1, operand2);
    default:  return 0;
  }
}



double evaluate_postfix(char expression[]) {
  stack *s = stack_init();

  // strtok() splits a string based on a delimiter and returns a pointer to 
  // tokens one at a time. strtok() modifies the string in the memory, so before
  // passing the string to the function, let's make a copy of it
  char expression_copy[EXPR_LENGTH];
  strcpy(expression_copy, expression);

  char *token = strtok(expression_copy, " ");

  while (token != NULL) {
    // atof() converts string to a double precision float value
    // 0 is returned, if the conversion fails.
    double val = atof(token);

    if (val) {
      // if the conversion is successful, so it's a operand (float value)
      // push the value on to the stack
      stack_push(s, &val, FLOAT);
    }
    else {
      // the conversion got failed, so it's an operator
      double operand2 = stack_pop(s)->element.dval;
      double operand1 = stack_pop(s)->element.dval;
      double res = evaluate(token[0], operand1, operand2);

      // update the result onto the stack
      stack_push(s, &res, FLOAT);
    }

    // update the token with the next block of the string
    token = strtok(NULL, " ");
  }

  // the final element in the stack, is the result of the entire expression
  return stack_pop(s)->element.dval;
}




/* Universe Starts here */
int main() {

  // declaring the postfix expressions (let's consider each expression is less than 80 chars)
  char expressions[EXPRESSIONS][EXPR_LENGTH] = {
    "3 5 +",
    "-19 9 + 4 -"
  };

  for (int i = 0; i < EXPRESSIONS; i++) {
    printf("(%s) = %lf \n", expressions[i], evaluate_postfix(expressions[i]));
  }

  return 0;
}