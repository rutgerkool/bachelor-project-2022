#ifndef UNIT_CLASS_H
#define UNIT_CLASS_H

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>
#include "function.hpp"

#define MAX_LINEAR_TEST_TIME        300000
#define MAX_QUADRATIC_TEST_TIME     40000000

int cycle_count = 1000;
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
    Category category;
    std::vector<int> problem_sizes;

    std::string return_test_category_string()
    {
        switch (category)
        {
        case CONSTANT_TIME:
            return "O(1)";
        case LOGARITHMIC_TIME:
            return "O(log(n))";
        case LINEAR_TIME:
            return "O(n)";
        case LINEARITHMIC_TIME:
            return "O(n log(n))";
        case QUADRATIC_TIME:
            return "O(n^2)";
        case FACTORIAL_TIME:
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
    std::vector<int> get_sizes()
    {
        switch (category)
        {
        case CONSTANT_TIME:
            return {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};    
        case LOGARITHMIC_TIME:
            return {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};    
        case LINEAR_TIME:
            //return {20, 40, 80, 160, 320, 640};
            //return {2,4,8,16,32,64};
            return {80, 160, 320, 640, 1280};
        case LINEARITHMIC_TIME:
            return {40, 80, 160, 320, 640, 1280};    
        case QUADRATIC_TIME:
            return {40, 80, 160, 320, 640};    
        case FACTORIAL_TIME:
            return {2, 4, 6, 8, 10, 12};
            //return {4,5,6,7,8};    
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

        sum = std::accumulate(running_times.begin(), running_times.end(), 0.0);
        mean = sum / running_times.size();

        for (double x : running_times) {
            std += pow(x - mean, 2);
        }

        std = sqrt(std / running_times.size());

        for (double time : running_times) {
            if (get_z_score(time, mean, std) < 3 && get_z_score(time, mean, std) > -3) {
                filtered_running_times.push_back(time);
            } 
        }
        
        running_times = filtered_running_times;

        std::cerr << "Mean: " << mean << " and std: " << std << std::endl;

        return running_times;
    }

    int get_expected_time(std::vector<double> average_times, int i)
    {
        switch (category)
        {
        case CONSTANT_TIME:
            return average_times[0];    
        case LOGARITHMIC_TIME:
            return average_times[0] + log2(problem_sizes[i]);  
        case LINEAR_TIME:
            return 2 * average_times.at(i);
        case LINEARITHMIC_TIME:
            return average_times[i] * (log2(problem_sizes[i + 1]) / 2);     
        case QUADRATIC_TIME:
            return 4 * average_times[i];  
        case FACTORIAL_TIME:
            return average_times[i] * (fact(problem_sizes[i + 1]) / fact(problem_sizes[i]));  
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
        return average_time < 0.90 * expected_time || average_time > 1.10 * expected_time;
    }

    bool is_linearithmic_time(double average_time, double expected_time)
    {
        return average_time < 0.80 * expected_time || average_time > 1.20 * expected_time;
    }

    bool is_quadratic_time(double average_time, double expected_time)
    {
        return average_time < 0.80 * expected_time || average_time > 1.20 * expected_time;
    }

    bool is_factorial_time(double average_time, double expected_time)
    {
        return average_time < 0.75 * expected_time || average_time > 1.25 * expected_time;
    }

    bool is_time(double average_time, double expected_time)
    {
        switch (category)
        {
        case CONSTANT_TIME:
            return is_constant_time(average_time, expected_time);    
        case LOGARITHMIC_TIME:
            return is_logarithmic_time(average_time, expected_time);    
        case LINEAR_TIME:
            return is_linear_time(average_time, expected_time);    
        case LINEARITHMIC_TIME:
            return is_linearithmic_time(average_time, expected_time);    
        case QUADRATIC_TIME:
            return is_quadratic_time(average_time, expected_time);    
        case FACTORIAL_TIME:
            return is_factorial_time(average_time, expected_time);    
        }
        return false;
    }

    int get_fail_count(std::vector<double> average_times)
    {
        int fail_count = 0;
        for (int i = 0; i < average_times.size() - 1; i++) {
            double expected_time = get_expected_time(average_times, i);

            if (is_time(average_times.at(i + 1), expected_time)) {
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
        std::string category_name = return_test_category_string();
        std::cerr << "Testing for " << category_name << ":" << std::endl;

        int fail_count = get_fail_count(average_times);
        if (fail_count > 1) {
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

    int print_test_results(bool is_in_category) 
    {
        std::string category_name = return_test_category_string();
        
        if (is_in_category) {
            std::cout << "SUCCESS\n" << std::endl;
            std::cerr << "\033[1;32mSUCCESS\033[0m\n" << std::endl;
            std::cout << "Function is in " << category_name << "\n";
            return 0;    
        }
        else {
            std::cout << "FAIL\n" << std::endl;
            std::cerr << "\033[1;31mFAIL\033[0m\n" << std::endl;
            std::cout << "Function is not in " << category_name << "\n"; 
            return 1;
        }
    } 

    double get_average_time(std::vector<double> running_times, int problem_size)
    {
        std::vector<double> filtered_times = running_times;
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
    Framework()
    {
        this->category = student_function::category;
        if (student_function::problem_sizes.size() == 0)
        {
            this->problem_sizes = get_sizes();
        }
        else 
        {
            this->problem_sizes = student_function::problem_sizes;
        }
    }

    int test_function() 
    {
        std::vector<double> average_times;
        for (int problem_size : problem_sizes)
        {
            std::vector<double> running_times;
            double average_time = 0;
            for (int j = 0; j < cycle_count; j++) 
            {
                student_function::initialize(problem_size);
                auto start = std::chrono::high_resolution_clock::now();
                student_function::run();
                auto end = std::chrono::high_resolution_clock::now();

                double time_taken = std::chrono::duration<double, std::nano>(end-start).count();
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

        if (print_test_results(is_in_category(average_times)) == 0) return 0;

        return -1;
    }
};

#endif /* UNIT_CLASS_H */
