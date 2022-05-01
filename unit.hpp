#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <functional>
#include <vector>

using namespace std;

vector<int> return_random_vector(int size);
int run_test_case(vector<int> v, function<int(vector<int>)> f);
int run_test_case(int x, function<int(int)> f);
void run_all_test_cases(function<int(int)> f) ;
void run_all_test_cases(function<int(vector<int>)> f);

#endif /* UNIT_H */
