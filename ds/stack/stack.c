#include "stack.h"

stack* stack_init() {
  // allocate memory for stack
  stack *s = malloc(sizeof(stack));
  if (s == NULL) {
    perror("stack_init() | Can't allocate memory for stack");
    exit(EXIT_FAILURE);
  }

  // define top to -1 to specify no element present in stack
  s->top = -1;

  return s;
}



bool is_stack_empty(stack *s) {
  return (s->top == -1);
}


bool is_stack_full(stack *s) {
  return (s->top >= STACK_SIZE - 1);
}



bool stack_push(stack *s, void *val, int vtype) {
  // check for Overflow Condition
  if (is_stack_full(s)) {
    perror("stack_push() | Overflow");
    return false;
  }

  // let's create a stack_element
  stack_element *se = malloc(sizeof(stack_element));
  if (se == NULL) {
    perror("stack_push() | Can't allocate memory for stack_element");
    return false;
  }

  // based on the value type, let's update the stack_element with the value
  switch (vtype) {
    case CHAR:
      se->element.cval = *(char *)val;
      break;
    case INT:
      se->element.ival = *(int *)val;
      break;
    case FLOAT:
      se->element.dval = *(double *)val;
      break;
    case STRING: {
      // let's calculate the string length
      int str_len = strlen( (char *)val );

      // allocate memory for the new string (+1 for null character)
      char *str = malloc( (str_len + 1) * sizeof(char) );
      if (str ==NULL) {
        perror("stack_push() | Can't allocate memory for new string");
        free(se);    // release the memory reserved for stack_element
        return false;
      }

      // copy the string from val to new str
      strcpy(str, (char *)val);

      se->element.sval = str;
      break;
    }
    default:
      perror("stack_push() | Invalid element type");
      free(se);
      return false;
  }

  // update the type of the element
  se->etype = vtype;

  // adding the stack with this new stack_element
  s->top++;
  s->items[s->top] = se;
  return true;
}



bool stack_push_selement(stack *s, stack_element *se) {
  // check for Overflow Condition
  if (is_stack_full(s)) {
    perror("stack_push_selement() | Overflow");
    return false;
  }

  s->top++;
  s->items[s->top] = se;
  return true;
}



stack_element* stack_pop(stack *s) {
  // check for Underflow condition
  if (is_stack_empty(s)) {
    perror("stack_pop() | Underflow");
    return NULL;
  }

  return s->items[s->top--];
}



const stack_element* stack_peek(stack *s) {
  // check for Underflow condition
  if (is_stack_empty(s)) {
    perror("stack_pop() | Underflow");
    return NULL;
  }

  return s->items[s->top];
}



void stack_cleanup(stack *s) {
  while (!is_stack_empty(s)) {
    stack_element *se = stack_pop(s);

    // if the element contain a string, then free the char array
    if (se->etype == STRING) free(se->element.sval);
    
    // free the stack_element
    free(se);
  }

  // finally free the stack itself
  free(s);
}