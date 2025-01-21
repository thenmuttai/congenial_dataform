/* Bashemin Parking Garage contains a single lane that hols up to ten cars.
 * There is only a single entrace/exit to the garage at one end of the lance. If
 * a customer arrives to pick up a car that is not nearest the exit, all cars
 * blocking its path are moved out, the customer's car is drive out and the other
 * cars are restored in the same order that they were in orginally. Write a 
 * program that processes a group of inputs lines. Each input line contains an 
 * 'A' for arrival or a 'D' for departure and license plate number. Cars are assumed
 * to arrive and depart in the order specified by the input. The program should
 * print a message whenever a car arrives or departs, when a car arrives, the
 * message should specify whether or not there is room for the car in garage. If
 * there is no room, the car leaves without entering the garage. When a car departs
 * the message should include the number of times that the car was moved out of the
 * garage to allow other cars to depart. 
 *
 * REF : Data Structures Using C and C++ - Exercise 2.2.8 
 */

#include "stack.h"

#define MAX_CAR   10

#define COUNT     7
#define COL       2
#define LICENSE   20



void car_arrival(stack *garage, char entry[COL][LICENSE]) {
  // does we have any space to park the car
  if (garage->top >= MAX_CAR - 1) {
    printf("[Arrival   | License plate - %s | No space for parking]\n", entry[1]);
    return;
  }

  // we have space left for the arriving car to park
  stack_push(garage, entry[1], STRING);
  printf("[Arrival   | License plate - %s | Availiable parking space - %d]\n", stack_peek(garage)->element.sval, MAX_CAR - garage->top - 1);
  return;
}



void car_departure(stack *garage, char entry[COL][LICENSE]) {
  // temprory parking space to move the cars to give way for a departing car
  stack *tmp_space = stack_init();

  int car_moved = 0;

  // check where the car is
  while (stack_peek(garage)) {
    // found the car
    if (strcmp(entry[1], stack_peek(garage)->element.sval) == 0) {
      // remove the car from the garage
      stack_element *car_leaving = stack_pop(garage);
      printf("[Departure | License plate - %s | Total car moved - %d]\n", car_leaving->element.sval, car_moved);

      // if any car were moved to tmp_space the move them back to the garage
      while (tmp_space->top > -1) {
        stack_element *move_back_car = stack_pop(tmp_space);
        stack_push(garage, move_back_car->element.sval, STRING);
      }

      // before returing destory the tmp space stack
      stack_cleanup(tmp_space);
      return;
    }
    else {
      // move a car from parking space to tmp space
      stack_element *move_car = stack_pop(garage);
      stack_push(tmp_space, move_car->element.sval, STRING);
    }
    car_moved++;
  }
}




void bashemin_parking_garage(stack *garage, char entry[COL][LICENSE]) {
  if (strcmp("A", entry[0]) == 0)
    car_arrival(garage, entry);        // car arrival
  else
    car_departure(garage, entry);      // car departure
}




// ALL STARTS HERE
int main() {
  stack *garage = stack_init();

  // [5][2][20]  - [inputs][size_of_each_input][last_input_string]
  char data[COUNT][COL][LICENSE] = {
    "A", "ABC 76 1111",
    "A", "DEC 75 2222",
    "A", "AXE 22 7894",
    "A", "RDE 21 8744",
    "D", "DEC 75 2222",
    "A", "WEX 12 2345",
    "D", "ABC 76 1111",
  };

  for (int c = 0; c < COUNT; c++) {
    bashemin_parking_garage(garage, data[c]);
  }

  return 0;
}
