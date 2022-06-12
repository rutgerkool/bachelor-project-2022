#include <iostream>
#include <vector>
int findSmallestMissingNumber( const std::vector<int> numbers) {
    int x = numbers.size();   
    int smallestNumber;
    int smallestMissingNum;
    smallestNumber = numbers.at(0);
    for (int i = 1; i < x; i++){  
        if ( numbers.at(i) <= smallestNumber ) {
            smallestNumber = numbers.at(i);
        }   
    }
   
   smallestMissingNum = smallestNumber + 1;
    for (int i = 0; i < x; i++) {
        if (smallestMissingNum == numbers.at(i)) {
            smallestMissingNum++;
        }
        for (int i =0; i < x; i++) {
        if (smallestMissingNum == numbers.at(i)){
            smallestMissingNum++;
        }
        }
    }
    
    return smallestMissingNum;
}
int main () {
    int x;
    std::cout << "How many numbers? " << std::endl;
    std::cin >> x;
    std::vector<int>inputNumbers(x);
    std::cout << "Please enter the numbers " << std::endl;
    
    for (int i = 0; i < x; i++) {
        std::cin >> inputNumbers.at(i);
        
    }
    std::cout << "The smallest missing number is " << findSmallestMissingNumber ( inputNumbers ) << std::endl;
}
