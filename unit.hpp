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
#include <string>

#define TEST_CASE(f) run_all_test_cases(f, #f)

using namespace std;
vector<int> return_smallest_missing_vector(int size);
vector<int> return_random_vector(int size);
double run_test_case(int x, function<int(int)> f); 
void run_all_test_cases(function<int(int)> f, const std::string& funcName);

#endif /* UNIT_H */
