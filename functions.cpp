#include <iostream>
#include <vector>
#include <cmath>
#include "unit.hpp"

using namespace std;

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

int find_max(vector<int> v) {

    int max = -1;

    for (int x : v) {
        if (x > max) 
            max = x;
    }

    return max;
}

int main() 
{
    TEST_CASE(const_1);
    TEST_CASE(sum);
    TEST_CASE(sum_2);
    TEST_CASE(sum_log);

    return 0;
}
