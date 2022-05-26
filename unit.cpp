#include "unit.hpp"

#define CONSTANT_NUM                0
#define LOGARITHMIC_NUM             1
#define LINEAR_NUM                  2
#define LINEARITHMIC_NUM            3
#define QUADRATIC_NUM               4
#define FACTORIAL_NUM               5

#define NRUNS_STANDARD              1000
#define NRUNS_LOGARITHMIC           1000
#define NRUNS_CONSTANT              2000000
#define MAX_CONSTANT_TEST_TIME      1000
#define MAX_LOGARITHMIC_TEST_TIME   10000
#define MAX_LINEAR_TEST_TIME        2000000
#define MAX_QUADRATIC_TEST_TIME     40000000

#define MAX_QUADRATIC_RUN_TIME      100000000

int cycle_count = NRUNS_STANDARD;
int max_run_time = 100000000;
int max_test_time = MAX_QUADRATIC_TEST_TIME;

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

std::vector<int> return_smallest_missing_vector(int size) 
{
    std::vector<int> v(size);

    for (int i = 0; i < v.size(); i++) {
        v[i] = v.size() - i - 1;
    }

    return v;
} 

std::vector<int> return_random_vector(int size) 
{
    std::vector<int> v(size);
    srand((unsigned)time(0)); 

    for (int i = 0; i < size; i++) {
        v[i] = rand() % size;
    }

    return v;
} 

double run_test_case(int x, std::function<int(int)> f) 
{
    auto t_start = std::chrono::high_resolution_clock::now();
    f(x);    
    auto t_end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::nano>(t_end-t_start).count();
}

std::vector<int> get_quadratic_sizes() 
{
    std::vector<int> problem_sizes{40};

    for (int i = 0; i < 5; i++) {
        problem_sizes.push_back(problem_sizes[i] * 2);
    }

    return problem_sizes;
}

std::vector<int> get_linear_sizes() 
{
    std::vector<int> problem_sizes{1000};

    for (int i = 0; i < 9; i++) {
        problem_sizes.push_back(problem_sizes[i] * 2);
    }

    return problem_sizes;
}

std::vector<int> get_logarithmic_sizes() 
{
    std::vector<int> problem_sizes{1, 10};

    for (int i = 2; i < 10; i++) {
        problem_sizes.push_back(pow(problem_sizes[1], i));
    }

    return problem_sizes;
}

std::vector<int> get_linearithmic_sizes() 
{
    std::vector<int> problem_sizes{1, 10};

    for (int i = 2; i < 7; i++) {
        problem_sizes.push_back(pow(problem_sizes[1], i));
    }

    return problem_sizes;
}

std::vector<int> get_factorial_sizes() 
{
    std::vector<int> problem_sizes{4};

    for (int i = 0; i < 5; i++) {
        problem_sizes.push_back(problem_sizes[i] + 1);
    }

    return problem_sizes;
}

std::vector<int> get_sizes(int category_number)
{
    switch (category_number)
    {
    case CONSTANT_NUM:
        return get_logarithmic_sizes();    
    case LOGARITHMIC_NUM:
        return get_logarithmic_sizes();    
    case LINEAR_NUM:
        return get_linear_sizes();    
    case LINEARITHMIC_NUM:
        return get_linearithmic_sizes();    
    case QUADRATIC_NUM:
        return get_quadratic_sizes();    
    case FACTORIAL_NUM:
        return get_factorial_sizes();    
    }
    return get_logarithmic_sizes();
}

double get_z_score(double x, double mean, double std)
{
    return (x - mean) / std;
}

std::vector<double> get_filtered_times(std::vector<double> running_times)
{
    std::vector<double> filtered_running_times;
    double std, mean, sum = 0.0;
    
    // double sq_sum = std::inner_product(running_times.begin(), running_times.end(), running_times.begin(), 0.0);
    // double std = std::sqrt(sq_sum / running_times.size() - mean * mean);
    
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

    std::cout << "Mean: " << mean << " and std: " << std << std::endl;

    return running_times;
}

std::vector<double> get_running_times(std::function<int(int)> f, int problem_size)
{
    std::vector<double> running_times;
    for (int j = 0; j < cycle_count; j++) {
        double time_taken = run_test_case(problem_size, f);
        running_times.push_back(time_taken);

        if (time_taken > max_run_time) {
            std::cout << std::fixed << std::setprecision(2) << time_taken << " and max " << max_test_time << std::endl;
            std::cout << "\nExecution aborted due to exceeding of maximum time: ";
            running_times.erase(running_times.begin(), running_times.end());
            running_times.push_back(-1);
            return running_times;
        }
    }
    std::cout << std::endl;

    return running_times;
}

double get_average_time(std::function<int(int)> f, int problem_size) 
{
    std::vector<double> running_times = get_running_times(f, problem_size);
    if (running_times.at(0) == -1) return -1;

    std::vector<double> filtered_times = get_filtered_times(running_times);
    double max_time = *std::max_element(running_times.begin(), running_times.end());
    double total_time = std::accumulate(filtered_times.begin(), filtered_times.end(), 0.0);
    double average_time = total_time / filtered_times.size();
   
    std::cout << "[Size: " << std::left << std::setw(10) << problem_size << "]";
    std::cout << std::fixed << std::setprecision(2) << "    Average time: " << average_time
    << " ns" << std::left << std::setw(10) << "    Max_time: " << max_time << " ns" << std::endl;

    if (average_time > max_test_time) {
        std::cout << "\nExecution aborted due to exceeding of maximum time: ";
        return -1;
    }

    return average_time;
}

std::vector<double> get_average_times(std::function<int(int)> f, std::vector<int> problem_sizes) 
{
    std::vector<double> average_times;
    for (int i = 0; i < problem_sizes.size(); i++) {
        double average_time = 0;
        
        average_time = get_average_time(f, problem_sizes[i]);
        if (average_time == - 1) {
            average_times.push_back(-1);
            return average_times;
        }
        average_times.push_back(average_time);
    }
    std::cout << std::endl;

    return average_times;
}

bool is_constant_time(double average_time, double expected_time)
{
    return average_time < 0.97 * expected_time || average_time > 1.03 * expected_time;
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
    return average_time < 0.85 * expected_time || average_time > 1.15 * expected_time;
}

bool is_factorial_time(double average_time, double expected_time)
{
    return average_time < 0.80 * expected_time || average_time > 1.20 * expected_time;
}

int get_expected_time(std::vector<double> average_times, std::vector<int> problem_sizes, int i, int category_number)
{
    switch (category_number)
    {
    case CONSTANT_NUM:
        return accumulate(average_times.begin(), average_times.end(), 0.0) / average_times.size();    
    case LOGARITHMIC_NUM:
        return average_times[0] + log2(problem_sizes[i]);  
    case LINEAR_NUM:
        return 2 * average_times.at(i);
    case LINEARITHMIC_NUM:
        return (average_times[0] + 1.5 * log2(problem_sizes[i]) * problem_sizes[i]);    
    case QUADRATIC_NUM:
        return 4 * average_times[i];  
    case FACTORIAL_NUM:
        return average_times[i - 1] * fact(problem_sizes[i]) / fact(problem_sizes[i - 1]);  
    }
    return -1;
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
    for (int i = 0; i < average_times.size() - 1; i++) {
        double expected_time = get_expected_time(average_times, problem_sizes, i, category_number);

        if (is_time(average_times.at(i + 1), expected_time, category_number)) {
            fail_count++;
            std::cout << average_times.at(i + 1) << " " << expected_time << " " << fail_count << std::endl;
        } 
    }

    return fail_count;
}

bool is_in_category(std::function<int(int)> f, int category_number)
{
    std::string category_name = return_test_category_string(category_number);
    std::cout << "Testing for " << category_name << ":" << std::endl;

    std::vector<int> problem_sizes = get_sizes(category_number);
    std::vector<double> average_times = get_average_times(f, problem_sizes);

    int fail_count = get_fail_count(average_times, problem_sizes, category_number);
    if (fail_count > 1) {
        std::cout << "Less than " << average_times.size() - 2 << "/" << average_times.size() - 1 << " tests passed: ";
        return false;
    }
    std::cout << average_times.size() - 1 - fail_count << "/" << average_times.size() - 1 << " tests passed: ";

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
        std::cout << "\033[1;32mSUCCESS\033[0m" << std::endl;
        std::cout << "\nFunction is in " << category_name << "\n" << std::endl;
        return 0;    
    }
    else {
        std::cout << "\033[1;31mFAIL\033[0m" << std::endl;
        std::cout << "\nFunction is not in " << category_name << "\n" << std::endl; 
        return 1;
    }
}

void run_all_test_cases(std::function<int(int)> f, const std::string& function_name) 
{
    std::cout << "\nTesting function " << function_name << std::endl << std::endl;

    for (int i = 0; i < 6; i++) {
        if (print_test_results(is_in_category(f, i), i) == 0) return;
    }
}
