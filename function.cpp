#include <iostream>
#include <vector>
#include "function.hpp"

std::vector<int> return_smallest_missing_vector(int size) 
{
    std::vector<int> v(size);

    for (int i = 0; i < v.size(); i++) 
    {
        v[i] = v.size() - i - 1;
    }

    return v;
} 

namespace student_function
{
    Category category = LINEAR_TIME;
    std::vector<int> problem_sizes = {};
    
    std::vector<int> v;

    static void initialize(int problem_size)
    {
        v = return_smallest_missing_vector(problem_size);
    }

    static int run()
    {
        findSmallestMissingNumber(v);
        
        return 0;
    }
}
