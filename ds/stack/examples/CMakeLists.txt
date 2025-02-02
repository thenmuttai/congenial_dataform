# specify the C standard
set(CMAKE_C_STANDARD 11)

# add the example source files
set(STACK_EXAMPLES
        is_the_equation_valid.c                       # problem 01
        parking_garage.c                              # problem 02
        implement_static_array_with_2_stack.c         # problem 03
        evaluate_postfix_expression.c                 # problem 04
        evaluate_prefix_expression.c                  # problem 05
        infix_to_postfix_expression.c                 # problem 06
        machine_with_one_register.c                   # problem 07
)

foreach(STACK_EXAMPLE ${STACK_EXAMPLES})
    # used to manipulate the file path, dir name, file name, file extension
    # "NAME_WE" means extract the filename without extension
    get_filename_component(FILE_NAME_WO_EXT ${STACK_EXAMPLE} NAME_WE)

    # generate executable for each source files
    add_executable(${FILE_NAME_WO_EXT} ${STACK_EXAMPLE})

    # link the stack_lib to each example executable
    target_link_libraries(${FILE_NAME_WO_EXT} PRIVATE stack_lib)

    # Link the math library only for problem 04 & problem 05
    if(FILE_NAME_WO_EXT STREQUAL "evaluate_postfix_expression" OR
        FILE_NAME_WO_EXT STREQUAL "evaluate_prefix_expression")
            target_link_libraries(${FILE_NAME_WO_EXT} PRIVATE m)
    endif()
endforeach()
