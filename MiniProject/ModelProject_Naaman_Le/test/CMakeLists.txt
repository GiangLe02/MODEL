# Nesrine Naaman & Nguyen Huong Giang LE

# Adding the test executable
add_executable(MyTestFile test.c ../main/src/inverse.c ../main/src/LU.c ../main/src/multiply_matrices.c ../main/src/function.c)

# Linking the math library and CUnit to the test executable
target_link_libraries(MyTestFile PRIVATE mylibrary)

# Registering the test executable with CTest
add_test(NAME Tests COMMAND MyTestFile)