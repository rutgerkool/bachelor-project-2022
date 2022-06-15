#ifndef UNIT_CLASS_H
#define UNIT_CLASS_H

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
#include "function.hpp"

#define main() main() {renamedMain(); return 0;} int foo()

#define NRUNS_STANDARD              1000
#define NRUNS_LOGARITHMIC           1000
#define NRUNS_CONSTANT              2000000
#define MAX_CONSTANT_TEST_TIME      10000
#define MAX_LOGARITHMIC_TEST_TIME   10000
#define MAX_LINEAR_TEST_TIME        300000
#define MAX_LINEARITHMIC_TEST_TIME  100000
#define MAX_QUADRATIC_TEST_TIME     40000000
#define MAX_QUADRATIC_RUN_TIME      10000000

#define CONSTANT_NUM                0
#define LOGARITHMIC_NUM             1
#define LINEAR_NUM                  2
#define LINEARITHMIC_NUM            3
#define QUADRATIC_NUM               4
#define FACTORIAL_NUM               5

int cycle_count = 10000;
int max_run_time = 100000000;
int max_test_time = MAX_QUADRATIC_TEST_TIME;


std::vector<int> return_random_vector(int size) 
{
    std::vector<int> v(size);
    srand((unsigned)time(0)); 

    for (int i = 0; i < size; i++) 
    {
        v[i] = rand() % size;
    }

    return v;
} 

class Framework
{
private:
    int category_number;
    std::vector<int> problem_sizes;

    std::string return_test_category_string(int category_number)
    {
        switch (category_number)
        {
        case CONSTANT_NUM:
            return "O(1)";
        case LOGARITHMIC_NUM:
            return "O(log(n))";
        case LINEAR_NUM:
            return "O(n)";
        case LINEARITHMIC_NUM:
            return "O(n log(n))";
        case QUADRATIC_NUM:
            return "O(n^2)";
        case FACTORIAL_NUM:
            return "O(n!)";
        }

        return "invalid category";
    }

    int fact(int n)
    {
        return (n == 0) || (n == 1) ? 1 : n * fact(n - 1);
    }

    /*
    To get the problem sizes for the right category.
    */
    std::vector<int> get_sizes(int category_number)
    {
        switch (category_number)
        {
        case CONSTANT_NUM:
            return {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};    
        case LOGARITHMIC_NUM:
            return {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};    
        case LINEAR_NUM:
            max_test_time = MAX_LINEAR_TEST_TIME;
            return {20, 40, 80, 160, 320, 640};
        case LINEARITHMIC_NUM:
            return {1, 10, 100, 1000, 10000};    
        case QUADRATIC_NUM:
            return {40, 80, 160, 320, 640};    
        case FACTORIAL_NUM:
            return {2, 4, 6, 8, 10, 12};    
        }
        return {-1};
    } 

    double get_z_score(double x, double mean, double std)
    {
        return (x - mean) / std;
    }

    std::vector<double> get_filtered_times(std::vector<double> running_times)
    {
        std::vector<double> filtered_running_times;
        double std, mean, sum = 0.0;
        
        bool time_is_removed = true;
        while (time_is_removed) {
            time_is_removed = false;

            sum = std::accumulate(running_times.begin(), running_times.end(), 0.0);
            mean = sum / running_times.size();

            for (double x : running_times) {
                std += pow(x - mean, 2);
            }

            std = sqrt(std / running_times.size());

            for (double time : running_times) {
                if (get_z_score(time, mean, std) < 1 && get_z_score(time, mean, std) > -1) {
                    filtered_running_times.push_back(time);
                } else {
                    time_is_removed = true;
                }
            }
            
            running_times = filtered_running_times;
            filtered_running_times.clear();
        }

        std::cerr << "Mean: " << mean << " and std: " << std << std::endl;

        return running_times;
    }

    int get_expected_time(std::vector<double> average_times, std::vector<int> problem_sizes, int i, int category_number)
    {
        switch (category_number)
        {
        case CONSTANT_NUM:
            return average_times[0];    
        case LOGARITHMIC_NUM:
            return average_times[0] + log2(problem_sizes[i]);  
        case LINEAR_NUM:
            return 2 * average_times.at(i);
        case LINEARITHMIC_NUM:
            return (average_times[0] + 1.5 * log2(problem_sizes[i]) * problem_sizes[i]);    
        case QUADRATIC_NUM:
            return 4 * average_times[i];  
        case FACTORIAL_NUM:
            std::cerr << fact(problem_sizes[i]) / fact(problem_sizes[i - 1]) << std::endl;
            return average_times[i - 1] * (fact(problem_sizes[i]) / fact(problem_sizes[i - 1]));  
        }
        return -1;
    }

    bool is_constant_time(double average_time, double expected_time)
    {
        return average_time < 0.9 * expected_time || average_time > 1.1 * expected_time;
    }

    bool is_logarithmic_time(double average_time, double expected_time)
    {
        return average_time < 0.90 * expected_time || average_time > 1.10 * expected_time;
    }

    bool is_linear_time(double average_time, double expected_time)
    {
        return average_time < 0.80 * expected_time || average_time > 1.20 * expected_time;
    }

    bool is_linearithmic_time(double average_time, double expected_time)
    {
        return average_time < 0.90 * expected_time || average_time > 1.10 * expected_time;
    }

    bool is_quadratic_time(double average_time, double expected_time)
    {
        return average_time < 0.80 * expected_time || average_time > 1.20 * expected_time;
    }

    bool is_factorial_time(double average_time, double expected_time)
    {
        return average_time < 0.75 * expected_time || average_time > 1.25 * expected_time;
    }

    bool is_time(double average_time, double expected_time, int category_number)
    {
        switch (category_number)
        {
        case CONSTANT_NUM:
            return is_constant_time(average_time, expected_time);    
        case LOGARITHMIC_NUM:
            return is_logarithmic_time(average_time, expected_time);    
        case LINEAR_NUM:
            return is_linear_time(average_time, expected_time);    
        case LINEARITHMIC_NUM:
            return is_linearithmic_time(average_time, expected_time);    
        case QUADRATIC_NUM:
            return is_quadratic_time(average_time, expected_time);    
        case FACTORIAL_NUM:
            return is_factorial_time(average_time, expected_time);    
        }
        return false;
    }

    int get_fail_count(std::vector<double> average_times, std::vector<int> problem_sizes, int category_number)
    {
        int fail_count = 0;
        for (int i = 1; i < average_times.size() - 1; i++) {
            double expected_time = get_expected_time(average_times, problem_sizes, i, category_number);

            if (is_time(average_times.at(i + 1), expected_time, category_number)) {
                fail_count++;
                std::cerr << average_times.at(i + 1) << " " << expected_time << " " << fail_count << std::endl;
            } else {
                std::cerr << "passed\n";
            }
        }

        return fail_count;
    }

    bool is_in_category(std::vector<double> average_times)
    {
        std::string category_name = return_test_category_string(category_number);
        std::cerr << "Testing for " << category_name << ":" << std::endl;

        int fail_count = get_fail_count(average_times, problem_sizes, category_number);
        if (fail_count > 2) {
            std::cerr << "Less than " << average_times.size() - 2 << "/" << average_times.size() - 1 << " tests passed: ";
            return false;
        }
        std::cerr << average_times.size() - 1 - fail_count << "/" << average_times.size() - 1 << " tests passed: ";

        for (int i = 0; i < average_times.size(); i++) {
            if (average_times[i] == -1) return false;
        }
        if (average_times.size() < 2) {
            return false;
        }
        return true;
    }

    int print_test_results(bool is_in_category, int category_number) 
    {
        std::string category_name = return_test_category_string(category_number);
        
        if (is_in_category) {
            std::cerr << "\033[1;32mSUCCESS\033[0m\n" << std::endl;
            std::cout << "Function is in " << category_name << "\n";
            return 0;    
        }
        else {
            std::cerr << "\033[1;31mFAIL\033[0m\n" << std::endl;
            std::cout << "Function is not in " << category_name << "\n"; 
            return 1;
        }
    } 

    double get_average_time(std::vector<double> running_times, int problem_size)
    {
        std::vector<double> filtered_times = get_filtered_times(running_times);
        double total_time = std::accumulate(filtered_times.begin(), filtered_times.end(), 0.0);
        double average_time = total_time / filtered_times.size();

        std::cerr << "[Size: " << std::left << std::setw(10) << problem_size << "]";
        std::cerr << std::fixed << std::setprecision(2) << "    Average time: " << average_time
        << " ns" << std::endl;

        if (average_time > max_test_time) {
            std::cerr << "\nExecution aborted due to exceeding of maximum time: ";
            return -1;
        }

        return average_time;
    }

    double check_running_time(double time_taken)
    {
        if (time_taken > max_run_time) {
            std::cerr << std::fixed << std::setprecision(2) << time_taken << " and max " << max_run_time << std::endl;
            std::cerr << "\nExecution aborted due to exceeding of maximum time: ";
            return -1;
        } else 
            return time_taken;
    }

public:
    Framework(int category_number);

    /*
    For the findSmallestMissingNumber() function. It runs the function with the problem sizes and then uses the functions 
    above to test for the corresponding category. Its return value could be passed to CodeGrade to indicate whether the 
    points should be given or not. 
    */
    int test_function() 
    {
        std::vector<double> average_times;
        for (int problem_size : problem_sizes)
        {
            std::vector<double> running_times;
            double average_time = 0;
            student_function::initialize(problem_size);
            for (int j = 0; j < cycle_count; j++) 
            {
                auto t_start = std::chrono::high_resolution_clock::now();
                student_function::run();   
                auto t_end = std::chrono::high_resolution_clock::now();

                double time_taken = std::chrono::duration<double, std::nano>(t_end-t_start).count();
                if (check_running_time(time_taken) == -1) 
                {
                    average_time = -1;
                    break;
                }
                running_times.push_back(time_taken);
            }
            average_time = get_average_time(running_times, problem_size);
            if (average_time == -1)
            {
                average_times.push_back(average_time);
                break;
            }
            average_times.push_back(average_time);
        }

        if (print_test_results(is_in_category(average_times), category_number) == 0) return 0;

        return -1;
    }
};

Framework::Framework(int category_number)
{
    this->category_number = category_number;
    this->problem_sizes = get_sizes(category_number);
}

int renamedMain();

#endif /* UNIT_CLASS_H */
