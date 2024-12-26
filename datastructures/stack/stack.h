#ifndef CD_STACK_HEADER
#define CD_STACK_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STACK_SIZE   100

#define CHAR   1
#define INT    2
#define FLOAT  3
#define STRING 4


/* struct to represent an Element in the Stack */
typedef struct {
  short etype;     // represents a value b/w 1 to 4 (CHAR, INT, FLOAT, STRING)
                   // depending on type of elements stored in element union     
  union {
    char   cval;
    int    ival;
    double dval;
    char   *sval;
  } element;
} stack_element;


/* struct to represent the Stack */
typedef struct {
  int top;         // indicate the position of current stack top

  // create an array of pointers to stack_element struct
  stack_element *items[STACK_SIZE];
} stack;



/* ---------- ---------- FUNCTION DECLERATIONS ---------- ----------     */
/**
 * @brief Allocate memory for Stack and returns the pointer.
 *        Also define the top to denote the stack is empty.
 * 
 * time complexity  -> O(1)
 * space complexity -> O(1)   // space allocated is const
 * 
 * @return stack* 
 */
stack* stack_init();

/**
 * @brief Verify if a stack is empty or not.
 * 
 * time complexity  -> O(1)
 * space complexity -> O(1)
 * 
 * @return true  -> in case the stack is empty
 * @return false -> in case the stack is not empty 
 */
bool is_stack_empty(stack *);

/**
 * @brief Verify if the stack is full or not.
 * 
 * time complexity  -> O(1)
 * space complexity -> O(1)
 * 
 * @return true  -> in case the stack is full.
 * @return false -> in case the stack has empty spaces.
 */
bool is_stack_full(stack *);

/**
 * @brief Add an value to the Stack.
 * 
 * time complexity  -> O(1)
 * space complexity -> O(1)
 *                     O(N) ; N -> len of the string
 * 
 * @param stack* Pointer to a Stack struct
 * @param void* Pointer to the value.
 * @param bool Specify the type of data (CHAR, INT, FLOAT, STRING)
 * @return true  -> if push operation is success
 * @return false -> if push operation fails 
 */
bool stack_push(stack *, void *, int);

/**
 * @brief Add stack element to the stack
 *
 * time complexity  -> O(1)
 * space complexity -> O(1)
 * 
 * @param stack_element* Pointer to a stack_element struct
 * @return true  -> if push operation is success
 * @return false -> if push operation fails 
 */
bool stack_push_selement(stack *, stack_element *);

/**
 * @brief Pop an element from top of the Stack.
 * 
 * time complexity  -> O(1)
 * space complexity -> O(1)
 * 
 * @param stack* Pointer to a stack struct
 * @return stack_element* -> Pointer to element that has been popped from stack
 * @return NULL -> if stack is empty (underflow condition)
 */
stack_element* stack_pop(stack *);

/**
 * @brief Get the last inserted element from stack, without removing it.
 *        const ensure that the caller function can't modify the stack_element
 * 
 * time complexity  -> O(1)
 * space complexity -> O(1)
 * 
 * @return const stack_element* -> Element at the top of the stack
 * @return NULL -> if stack is empty (underflow condition)
 */
const stack_element* stack_peek(stack *);

/**
 * @brief Free all the memory allocated.
 * 
 * time complexity  -> O(N)
 * space complexity -> O(1)
 * 
 * @param stack* Pointer to a stack struct
 */
void stack_cleanup(stack *);

#endif    /* CD_STACK_HEADER */