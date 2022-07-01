# OTEST: C++ Unit Testing For Time Complexity Analysis

This GitHub repository provides the source code of the OTEST unit testing framework, which is used to estimate the big-O category of arbitrary functions. The text below describes how to use and interact with the framework to test example or self-implemented functions. 

## Running the framework
After downloading or cloning the framework's source code and when setting the current working directory to project_main, the user can run different code examples by using the following commands:

    $ cat include.cpp examples/sm* function.cpp unit-class.cpp > 
    bigOtestFunction.cpp
    $ g++ -o bigOtestFunction bigOtestFunction.cpp
    $ ./bigOtestFunction


The first command concatenates the necessary source code files with the file in which the function to be tested is defined. In this case, the file(s) starting with "sm" from the examples directory will be used. 

The second and third command compile the file created by the first command and execute it to run the tests. 

### Running Arbitrary Functions
When the user wants to run specific functions in a separate file, the first command should be adapted so that "examples/sm*" is changed to the file in which the function is defined. The user can then specify which function to test, how to initialize this function, and which big-O category and problem sizes are included in the test in the function.cpp file. 

## Recreating the Evaluation Results
The evaluation results are obtained by using the results.cpp file to run the framework 100 times for a certain test case and outputting the number of times the big-O category to be tested for was assigned to the tested function. The test cases were specified manually by adapting the values of the cycle_count and problem_sizes variables to check for the accuracy of these values. The plot.py script was used to generate the plots that represent the results of these tests. The user of the framework can use the examples in the examples directory to reproduce these results. 