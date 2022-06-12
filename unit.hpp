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

#define main() main() {renamedMain(); return 0;} int foo()

#define CONSTANT_NUM                0
#define LOGARITHMIC_NUM             1
#define LINEAR_NUM                  2
#define LINEARITHMIC_NUM            3
#define QUADRATIC_NUM               4
#define FACTORIAL_NUM               5

#define TEST_CASE(f)          run_all_test_cases(f, #f)
#define TEST_CONSTANT(f)      run_test_case(f, #f, CONSTANT_NUM)
#define TEST_LOGARITHMIC(f)   run_test_case(f, #f, LOGARITHMIC_NUM)
#define TEST_LINEAR(f)        run_test_case(f, #f, LINEAR_NUM)
#define TEST_LINEARITHMIC(f)  run_test_case(f, #f, LINEARITHMIC_NUM)
#define TEST_QUADRATIC(f)     run_test_case(f, #f, QUADRATIC_NUM)
#define TEST_FACTORIAL(f)     run_test_case(f, #f, FACTORIAL_NUM)

std::vector<int> return_random_vector(int size);
double get_time_measure(int x, std::function<int(int)> f); 
int run_test_case(std::function<int(int)> f, const std::string& function_name, int category_number);
int run_test_case(std::function<int(std::vector<int>)> f, const std::string& function_name, int category_number);
int run_test_case(std::function<bool(int n, std::vector<std::vector<bool>>&, int row)> f, const std::string& function_name, int category_number); 
int run_all_test_cases(std::function<int(int)> f, const std::string& funcName);
int run_all_test_cases(std::function<int(std::vector<int>)> f, const std::string& function_name);
int run_all_test_cases(std::function<bool(int n, const std::vector<std::vector<bool>>&, int row)> f, const std::string& function_name);
int renamedMain();

#endif /* UNIT_H */
