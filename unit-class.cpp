
#include <iostream>
#include "unit-class.hpp"

int renamedMain()
{
    Framework framework(LINEAR_NUM);
    try 
    {
        framework.test_function();
    }
    catch (std::exception& e) 
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }
    return 0;
}
