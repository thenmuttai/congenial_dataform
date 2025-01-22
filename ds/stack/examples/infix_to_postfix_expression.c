#include "stack.h"

#define EXPRESSIONS   6     // total no of expression to convert
#define EXPR_LENGTH   30    // max length of expression


/* verify if the oper1 has higher precedence that oper2 */
bool is_precedence(char oper1, char oper2) {
  if (oper1 == '(')     // has lowest precedence
    return false;

  if (oper1 == '$')     // has highest precedence
    return true;

  if (oper1 == '*' || oper1 == '/') 
    return (oper2 == '*' || oper2 == '/' || oper2 == ')' || oper2 == '+' || oper2 == '-');

  if (oper1 == '+' || oper1 == '-') 
    return (oper2 == '+' || oper2 == '-' || oper2 == ')');

  return false;
}


bool is_operator(char oper) {
  return (oper == '+' || oper == '-' || oper == '*' || oper == '/' || oper == '$' || oper == '(' || oper == ')');
}


char* infix_to_postfix(char *expr) {
  stack *oper = stack_init();   // stack to hold the operators
  char *postfix = malloc(EXPR_LENGTH * sizeof(char));
                                // allocate memory for string which holds the result (postfix expression)
  int p = 0;                    // index counter for postfix sting

  for (int i = 0; i < strlen(expr); i++) {
    char current = expr[i];

    // if it's an operand, then add it to output string
    if ( !is_operator(current) ) {
      postfix[p++] = current;
      continue;
    }

    // if it's an operator, then do these
    if (current == '(')
      // 1. push '(' onto the stack
      stack_push(oper, &current, CHAR);

    else if (current == ')') {
      // 2. pop the stack until '(' is found and add it to the postfix expression
      while (!is_stack_empty(oper) && stack_peek(oper)->element.cval != '(')
        postfix[p++] = stack_pop(oper)->element.cval;
      
      // finally pop the opening parenthesis
      stack_pop(oper);
    }

    else {
      // 3. operator encountered
      // check the precedence of last push operator to current one
      // in case of higher precedence add it to postfix string else push it to stack
      while (!is_stack_empty(oper) && is_precedence(stack_peek(oper)->element.cval, current))
        postfix[p++] = stack_pop(oper)->element.cval;
      
      // simply push the operator if is_precedence returns false
      stack_push(oper, &current, CHAR);
    }
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
    "(A+B)*(C-D)",
    "A-B/(C*D$E)",
    "A$B*C-D+E/F/(G+H)",
    "((A+B)*C-(D-E))$(F+G)"
  };

  for (int idx = 0; idx < EXPRESSIONS; idx++)
    printf("%s = %s \n", expressions[idx], infix_to_postfix(expressions[idx]) );

  return 0;
}