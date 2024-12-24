cmake_minimum_required(VERSION 3.25)
project(CDStack)

# specify the C standard
set(CMAKE_C_STANDARD 11)

# add the stack source file
set(STACK_SRC stack.c)

# include the stack header file
set(STACK_HEADERS stack.h)

# generate a library from the stack source file
add_library(stack_lib ${STACK_SRC} ${STACK_HEADERS})

# make the library public so it can be linked in subdirectories
target_include_directories(stack_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



# create executable for the stack test file
add_executable(test_stack test_stack.c)


# link the stack library to test executable
target_link_libraries(test_stack PRIVATE stack_lib)



# add the examples directory
# this will search of CMakeLists file under examples dir and execute it
add_subdirectory(examples)