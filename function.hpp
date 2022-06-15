#include <iostream>
#include <vector> 

namespace student_function
{
    BST *binarySearchTree;

    static void initialize(int problem_size)
    {
        binarySearchTree = new BST;
        for (int i = 0; i < problem_size; i++) binarySearchTree->insertKey(i);
    }

    static void run()
    {
        binarySearchTree->inOrder();
    }
}
