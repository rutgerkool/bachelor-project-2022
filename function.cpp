#include <iostream>
#include <vector> 
#include "function.hpp"

namespace student_function
{
    Category category = LINEAR_TIME; // Indicate which big-O category needs to be tested
    std::vector<int> problem_sizes = {}; // Optional: specify which problem sizes need to be tested. 
                                        //  For linear/quadratic tests, these values need to increase by a factor of 2. 

    // Add aditional variables needed for initialization/running. 

    static void initialize(int problem_size)
    {
        // Specify how to initialize the function here given its problem size.
    }

    static int run()
    {
        // Specify which function to run here.

        return 0;
    }
}
