
#include <iostream>
#include "unit-class.hpp"

int renamedMain()
{
    Framework framework(LINEAR_NUM);
    BST* binarySearchTree = new BST;
    framework.test_function(binarySearchTree);

    return 0;
}
