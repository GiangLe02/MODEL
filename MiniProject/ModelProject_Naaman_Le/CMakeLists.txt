# Nesrine Naaman & Nguyen Huong Giang LE
# Minimum version required
cmake_minimum_required(VERSION 3.10)
project(MyProject LANGUAGES C)

# Project name and version
project(MyProject VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the executable for the main program
add_executable(my_program main/src/main.c main/src/function.c main/src/inverse.c main/src/LU.c main/src/multiply_matrices.c)

# Specify the output directory for the executable
set_target_properties(my_program PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Ensure the 'output' directory exists when building or running
add_custom_command(TARGET my_program POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/main/time_testing_output
)
add_subdirectory(main/src)

## Add the test directory
enable_testing()
add_subdirectory(test)