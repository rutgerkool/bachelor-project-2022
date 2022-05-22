#include <iostream>
#include <vector>
#include <cmath>
#include "unit.hpp"

int factorial_sum(int n)
{
    if (n == 0 || n == 1) return 1;

    int x = 0;
    for (int i = 1; i <= n; i++) {
        x += factorial_sum(n - 1);
    }

    return x;
}

int smallest_missing(int n) 
{
    std::vector<int> v = return_smallest_missing_vector(n);

    int smallest = -1;
    int count = 0;

    while (count < v.size()) {
        if ( v.at(count) == smallest+1 ){
            smallest = v.at(count);
            count = -1;
        }
        count++;
    }

    int smallest_missing = smallest + 1;

    return smallest_missing;
}

int sum(int n) 
{
    int x = 1;
    for (int i = 1; i <= n; i++) {
        x++;
    }

    return x;
}

int sum_log(int n)
{
    int count = 0;
    for (int i = 1; i < n; i = i * 2) {
        count++;
    }

    return count;
}   

int sum_nlog(int n)
{
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j = j * 2) {
            count++;
        }
    }

    return count;
}   

int sum_2(int n) 
{
    int x = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            x++;
        }
    }

    return x;
}

int const_1(int index) 
{
    if (index > 0) 
        return index;
    else
        return 0;
}

int find_max(std::vector<int> v) {

    int max = -1;

    for (int x : v) {
        if (x > max) 
            max = x;
    }

    return max;
}

int main() 
{
    TEST_CASE(sum_2);
    
    return 0;
}
