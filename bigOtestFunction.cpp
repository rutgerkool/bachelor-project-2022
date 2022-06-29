
#include "include.hpp"

#define main(...)                                   main() {run_framework(); return 0;} int foo(int argc, char *argv[])


#include <iostream>
#include <vector>
int findSmallestNumber(const std::vector<int> v){
    int smallest = v.at(0);
    for (int i=1; i<v.size(); i++){
        if ( v.at(i) < smallest ){
            smallest = v.at(i);
        }
    }
    return smallest;
}
int findSmallestMissingNumber(const std::vector<int> &v){
    std::vector<bool> missing(v.size(),true);
    const int smallest = findSmallestNumber(v);
    const int maxPossible = smallest + v.size() - 1;
    for (int i=0; i<v.size(); i++){
        if ( v.at(i) <= maxPossible ){
            missing.at(v.at(i) - smallest) = false;
        }
    }
    for (int i=0; i<missing.size(); i++){
        if ( missing.at(i) ){
            return smallest+i;
        }
    }
    return smallest+v.size();
}
int main(){
    int vectorSize;
    std::cout << "How many numbers? ";
    std::cin >> vectorSize;
    std::vector<int> inputVector(vectorSize);
    std::cout << "Please enter the numbers ";
    for ( int i=0; i<vectorSize; i++){
        std::cin >> inputVector.at(i);
    }
    const int smallestMissing = findSmallestMissingNumber(inputVector);
    std::cout << "The smallest missing number is " << smallestMissing << std::endl;
    return 0;
}

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

#include <iostream>
#include "unit-class.hpp"

int run_framework()
{
    Framework framework;
    return framework.test_function();
}
