#include <iostream>
#include <vector> 
#include "function.hpp"

namespace student_function
{
    Category category = LINEARITHMIC_TIME;
    std::vector<int> problem_sizes = {};

    BST *binarySearchTree;
    int current_problem_size;

    static void initialize(int problem_size)
    {
        binarySearchTree = new BST;
        current_problem_size = problem_size;
    }

    static int run()
    {
        for (int i = 0; i < current_problem_size; i++) binarySearchTree->insertKey(i);

        return 0;
    }
}

