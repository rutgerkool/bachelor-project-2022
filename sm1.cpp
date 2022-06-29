

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

