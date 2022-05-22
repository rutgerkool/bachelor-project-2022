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

std::vector<int> return_smallest_missing_vector(int size);
std::vector<int> return_random_vector(int size);
double run_test_case(int x, std::function<int(int)> f); 
void run_all_test_cases(std::function<int(int)> f, const std::string& funcName);

#endif /* UNIT_H */
