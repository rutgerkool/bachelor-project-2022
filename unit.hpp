#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <functional>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

vector<int> return_random_vector(int size);
double run_test_case(int x, function<int(int)> f); 
void run_all_test_cases(function<int(int)> f) ;
void run_all_test_cases(function<int(vector<int>)> f);

#endif /* UNIT_H */
