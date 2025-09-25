### MODEL Implementation Project

#### By Nesrine Naaman and Nguyen Huong Giang LE

After opening the 'Project_Final' folder, we have a CMakeLists.txt file, a test folder, for testing if we're obtaining correct matrix results using our functions, and a main folder, which contains: \n
* src folder for the source code
* time_testing_output folder for testing the time taken by our functions (will have txt log files produced by the program)
* graphs folder where we produced graphs showing the time complexities obtained of our algorithms 

To run this program, follow the steps:
1. Make a build directory for cmake. Run:
    ```
    mkdir build
    ```
2. Change the directory to the build folder
3. Run CMake to generate the build system
    ```
    cd build
    cmake ..
    ```
4. Build the project and the tests:
    ```
    make
    ```
5. Run the test
    ```
    ctest
    ```
6. Run the main program
    ```
    ./bin/my_program
    ```

<br>

Source used: https://cmake.org/getting-started/
