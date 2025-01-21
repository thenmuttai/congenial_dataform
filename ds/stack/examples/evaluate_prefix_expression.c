#include <math.h>

#include "stack.h"

#define EXPRESSIONS   3
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



/* Function split the expression using space as a delimiter and 
 * packs it into an array and returns it. */
char** split_and_packit(char expression[], int *size) {
  // making a copy of the expression string, as strtok() will modify the string
  // in memory while splitting it based on a delimiter
  char *expr_copy = strdup(expression);
  if (expr_copy == NULL) {
    fprintf(stderr, "split_and_packit() Failed to allocate memory for copy array");
    return 0;
  }

  // count no of tokens to allcoate memory for array to hold split up string
  int count = 0;
  char *token = strtok(expr_copy, " ");
  while (token != NULL) {
    count++;
    token = strtok(NULL, " ");
  }

  // allocate memeory for array of token(part of expression)
  char **expr_arr = malloc(count * sizeof(char *));

  // reset the copy and tokenize again
  strcpy(expr_copy, expression);

  // split the expression based on delimiter and add each part of string to array
  int idx = 0;
  token = strtok(expr_copy, " ");
  while (token != NULL) {
    expr_arr[idx++] = strdup(token);
    token = strtok(NULL, " ");
  }

  *size = count;
  return expr_arr;
}



double evaluate_prefix(char expression[]) {
  // stacks to hold the operands (as we loop over the expression)
  stack *s = stack_init();

  // split the expression based on delimiter and pack the result
  int size = 0;
  char **expr = split_and_packit(expression, &size);      // array of strings

  for (int token = size-1; token >= 0; token--) {
    // atof() converts string to a double precision float value
    // 0 is returned, if the conversion fails.
    double val = atof( expr[token] );

    if (val) {
      // conversion is successful, so it's a operand (float value)
      // push the value on to the stack
      stack_push(s, &val, FLOAT);
    }
    else {
      // the conversion got failed, so it's an operator
      double operand1 = stack_pop(s)->element.dval;
      double operand2 = stack_pop(s)->element.dval;
      double res = evaluate(expr[token][0], operand1, operand2);

      // update the result onto the stack
      stack_push(s, &res, FLOAT);
    }
  }

  // the final element in the stack, is the result of the entire expression
  return stack_pop(s)->element.dval;
}







/* EVERY THING STARTS HERE */
int main() {
  char expressions[EXPRESSIONS][EXPR_LENGTH] = {
    "+ 5 6",
    "- + 5 6 3",
    "* + 2 4 - 9 5"
  };

  for (int idx = 0; idx < EXPRESSIONS; idx++)
    printf("(%s) = %lf \n", expressions[idx], evaluate_prefix(expressions[idx]) );

  return 0;
}