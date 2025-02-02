/*
Assume a machine has a single registor and six instructions.

LD  A    ;Place operand A into the registor
ST  A    ;Place content of registor in to the variable A
AD  A    ;Add content of var A to the registor
SB  A    ;Substracts content of var A from the registor
ML  A    ;Multiply contents of var A by the registor
DV  A    ;divide content of registor by variable A

Write a program that accepts a postfix expression containing single letter
operands and the operators +. -. *. / and print the sequence of instruction
to evaluate the expression and leave the results in the registor.
*/

#include "stack.h"

// returns the instruction associated with the operator
char* oper_to_instru(char oper) {
  switch (oper) {
    case '+': return "AD";
    case '-': return "SB";
    case '*': return "ML";
    case '/': return "DV";
    default:  return "";
  }
}


bool is_operator(char oper) {
  switch (oper) {
    case '+':
    case '-':
    case '*':
    case '/':
      return true;
    default: 
      return false;
  }
}


void print_instruction(char operand1, char operand2, char operator, char *temp) {
  // load operand1 into the registor
  if (atoi(&operand1))
    printf("%5s %9s%c \n", "LD", "TEMP", operand1);
  else
    printf("%5s %9c \n", "LD", operand1);

  // do the evaluation using operand2
  if (atoi(&operand2))
    printf("%5s %9s%c \n", oper_to_instru(operator), "TEMP", operand2);
  else
    printf("%5s %9c \n", oper_to_instru(operator), operand2);

  // copy the content of registor into a variable
  printf("%5s %9s%c \n", "ST", "TEMP", *temp);
}


/* SOLUTION */
void convert_to_machine_instruction(char *expr) {
  char temp = '1';

  // stack to hold parts of the expression for evaluation
  stack *s = stack_init();

  for (int i = 0; i < strlen(expr); i++) {
    // if it's an operand then push it to the stack
    if ( !is_operator(expr[i]) ) {
      stack_push(s, &expr[i], CHAR);
      continue;
    }

    // if it's an operator, then pop element from stack and evaluate
    char operand2 = stack_pop(s)->element.cval;
    char operand1 = stack_pop(s)->element.cval;

    print_instruction(operand1, operand2, expr[i], &temp);

    // adding the temp variable count back into the stack
    stack_push(s, &temp, CHAR);
    temp++;
  }
}





/* ALL STARTS HERE */
int main() {
  // input expression 
  char input_expr[] = "ABC*+DE-/";

  convert_to_machine_instruction(input_expr);

  return 0;
}


