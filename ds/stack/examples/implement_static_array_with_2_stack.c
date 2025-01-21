#include "stack.h"


bool is_index_outofbounds(stack *s, int idx) {
  return (idx > s->top || idx < 0);
}

stack* array_init(int capacity, int etype) {
  if (capacity > STACK_SIZE) return NULL;

  // initialize a stack (which act as array)
  stack *arr = stack_init();

  // update default for all the slots of the array(stack)
  for (int i = 0; i < capacity; i++) {
    switch(etype) {
      case CHAR:
      case INT:
      case FLOAT: {
        int default_val = 0;
        stack_push(arr, &default_val, etype);
        break;
      }
      case STRING: {
        char default_str[] = "";
        stack_push(arr, default_str, etype);
        break;
      }
      default:
        puts("INVALID ELEMENT TYPE");
        return NULL;
    }
  }
  return arr;
}



bool array_update(stack *arr, int idx, void *val) {
  // check for outofbound error
  if (is_index_outofbounds(arr, idx)) return false;

  // get the value type (since it's a homogenous static array)
  int etype = arr->items[0]->etype;

  // move all the elements on top of the idx element
  // to a temp_stack to update the idx element and again push back
  stack *tmp_stack = stack_init();

  while (arr->top >= 0) {
    if (arr->top == idx) {
      stack_pop(arr);
      stack_push(arr, val, etype);

      // if any elements are moved out, then add the elements back
      while (tmp_stack->top > -1) {
        stack_push_selement(arr, stack_pop(tmp_stack));
      }
      break;
    }

    // pop the elements and move it to the tmp stack untile the idx matches the top
    stack_push_selement(tmp_stack, stack_pop(arr));
  }
  return true;
}



stack_element* array_get(stack *arr, int idx) {
  // check for outofbound error
  if (is_index_outofbounds(arr, idx)) return NULL;

  // move all the elements of top of idx element to a tmp_stack
  // get the element and again push back the elements from tmp_stack
  stack *tmp_stack = stack_init();

  while (arr->top >= 0) {
    if (idx == arr->top) {
      stack_element *ele = stack_peek(arr);

      // if any elements are moved out, then add the elements back
      while (tmp_stack->top > -1) {
        stack_push_selement(arr, stack_pop(tmp_stack));
      }

      return ele;
    }

    // pop the elements and move it to the tmp stack untile the idx matches the top
    stack_push_selement(tmp_stack, stack_pop(arr));
  }
  return NULL;
}


void array_cleanup(stack *arr) {
  stack_cleanup(arr);
}




/* ITS TIME TO TEST THE ARRAY IMPLEMENTATION OF STACK */
void test_array_functions() {
  // Initialize an array of integers with a capacity of 5
  stack *arr = array_init(5, INT);
  if (arr == NULL) {
      printf("Failed to initialize array.\n");
      return;
  }

  // Update the array with some values
  int values[] = {10, 20, 30, 40, 50};
  for (int i = 0; i < 5; i++) {
      if (!array_update(arr, i, &values[i])) {
          printf("Failed to update index %d.\n", i);
      }
  }

  // Retrieve and print values from the array
  for (int i = 0; i < 5; i++) {
      stack_element *ele = array_get(arr, i);
      if (ele != NULL) {
          printf("Value at index %d: %d\n", i, ele->element.ival);
      } else {
          printf("Failed to get value at index %d.\n", i);
      }
  }

  // Test out-of-bounds conditions
  if (array_update(arr, 5, &values[0])) {
      printf("Out-of-bounds update should have failed.\n");
  }
  if (array_get(arr, 5) != NULL) {
      printf("Out-of-bounds get should have returned NULL.\n");
  }

  // Clean up
  // Assuming a function to free the stack is available
  array_cleanup(arr);
}





/* Execution starts here */
int main() {
  test_array_functions();

  return 0;
}
