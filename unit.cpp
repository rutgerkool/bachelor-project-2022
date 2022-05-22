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

enum big_o_category {
    CONSTANT = 0,
    LINEAR = 1,
    LOGARITHMIC,
    QUADRATIC = 2
};

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

double get_z_score(double x, double mean, double std)
{
    return (x - mean) / std;
}

std::vector<double> get_filtered_times(std::vector<double> running_times)
{
    std::vector<double> filtered_running_times;
    
    double sum = std::accumulate(running_times.begin(), running_times.end(), 0.0);
    double mean = sum / running_times.size();

    double sq_sum = std::inner_product(running_times.begin(), running_times.end(), running_times.begin(), 0.0);
    double std = std::sqrt(sq_sum / running_times.size() - mean * mean);

    std::cout << "Mean: " << mean << " and std: " << std << std::endl;
    
    for (double time : running_times) {
        if (get_z_score(time, mean, std) < 1 && get_z_score(time, mean, std) > -1)
            filtered_running_times.push_back(time);
    }

    return filtered_running_times;
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
    double max_time = *std::max_element(filtered_times.begin(), filtered_times.end());
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

bool is_constant(std::function<int(int)> f)
{
    std::cout << "Testing for O(1):" << std::endl;

    cycle_count = 1000;
    max_test_time = MAX_CONSTANT_TEST_TIME;

    std::vector<int> problem_sizes = get_logarithmic_sizes();

    std::vector<double> average_times = get_average_times(f, problem_sizes);

    cycle_count = NRUNS_STANDARD;

    double expected_time = accumulate(average_times.begin(), average_times.end(), 0.0) / average_times.size();

    int fail_count = 0;
    int pass_count = 0;

    for (int i = 0; i < average_times.size(); i++) {

        if (average_times[i] < 0.97 * expected_time || average_times[i] > 1.03 * expected_time) {
            fail_count++;

            if (fail_count > 2) {
                std::cout << "Less than " << average_times.size() - 2 << "/" << average_times.size() << " tests passed: ";
                return false;
            }
        }
        else {
            pass_count++;
        }
    }

    std::cout << pass_count << "/" << average_times.size() << " tests passed: ";

    for (int i = 0; i < average_times.size(); i++) {
        if (average_times[i] == -1)
            return false;
    }

    return true;
}

bool is_linear(std::function<int(int)> f)
{
    std::cout << "Testing for O(n):" << std::endl;

    max_test_time = MAX_LINEAR_TEST_TIME;
    max_run_time = 2000000;

    std::vector<int> problem_sizes = get_linear_sizes();

    std::vector<double> average_times = get_average_times(f, problem_sizes);
    
    int fail_count = 0;
    int pass_count = 0;

    for (int i = 0; i < average_times.size() - 1; i++) {
        double expected_time = 2 * average_times[i];
        
        if (average_times[i + 1] < 0.80 * expected_time || average_times[i + 1] > 1.20 * expected_time) {
            fail_count++;
            if (fail_count > 2) {
                std::cout << "Less than " << average_times.size() - 3 << "/" << average_times.size() - 1 << " tests passed: ";
                return false;
            }
        }
        else {
            pass_count++;
        }
    }

    std::cout << pass_count << "/" << average_times.size() - 1 << " tests passed: ";

    for (int i = 0; i < average_times.size(); i++) {
        if (average_times[i] == -1)
            return false;
    }

    if (average_times.size() >= 2) {
        return true;
    }
    else 
        return false;
}

bool is_quadratic(std::function<int(int)> f)
{
    std::cout << "Testing for O(n^2):" << std::endl;

    max_test_time = MAX_QUADRATIC_TEST_TIME;
    max_run_time = MAX_QUADRATIC_RUN_TIME;

    std::vector<int> problem_sizes = get_quadratic_sizes();

    std::vector<double> average_times = get_average_times(f, problem_sizes);

    int fail_count = 0;
    for (int i = 0; i < average_times.size() - 1; i++) {
        double expected_time = 4 * average_times[i];

        if (average_times[i + 1] < 0.85 * expected_time || average_times[i + 1] > 1.15 * expected_time) {
            fail_count++;
            if (fail_count > 1) {
                std::cout << "Less than " << average_times.size() - 2 << "/" << average_times.size() - 1 << " tests passed: ";
                return false;
            }
        } 
    }
    std::cout << average_times.size() - 1 - fail_count << "/" << average_times.size() - 1 << " tests passed: ";

    for (int i = 0; i < average_times.size(); i++) {
        if (average_times[i] == -1) return false;
    }

    return true;
}

bool is_logarithmic(std::function<int(int)> f)
{
    std::cout << "Testing for O(log(n)):" << std::endl;

    cycle_count = NRUNS_LOGARITHMIC;
    max_test_time = MAX_LOGARITHMIC_TEST_TIME;
    max_run_time = 100000;
    
    std::vector<int> problem_sizes = get_logarithmic_sizes();

    std::vector<double> average_times = get_average_times(f, problem_sizes);

    cycle_count = NRUNS_STANDARD;
    max_test_time = MAX_QUADRATIC_TEST_TIME;

    int pass_count = 0;
    int fail_count = 0;

    for (int i = 0; i < average_times.size() - 1; i++) {
        double expected_time = average_times[0] + log2(problem_sizes[i]);
        if (average_times[i + 1] < 0.90 * expected_time || average_times[i + 1] > 1.10 * expected_time) {
            fail_count++;
            if (fail_count > 1) {
                std::cout << "Less than " << average_times.size() - 2 << "/" << average_times.size() - 1 << " tests passed: ";
                return false;
            }
        }
        else {
            pass_count++;
        }
    }

    std::cout << pass_count << "/" << average_times.size() - 1 << " tests passed: ";

    for (int i = 0; i < average_times.size(); i++) {
        if (average_times[i] == -1)
            return false;
    }

    if (average_times.size() >= 2) {
        return true;
    }
    else 
        return false;
}

bool is_linearithmic(std::function<int(int)> f)
{
    std::cout << "Testing for O(n log(n)):" << std::endl;

    cycle_count = NRUNS_STANDARD;
    max_test_time = MAX_QUADRATIC_TEST_TIME;
    max_run_time = MAX_QUADRATIC_TEST_TIME;
    
    std::vector<int> problem_sizes = get_linearithmic_sizes();

    std::vector<double> average_times = get_average_times(f, problem_sizes);

    int fail_count = 0;
    int pass_count = 0;

    for (int i = 1; i < average_times.size(); i++) {
        double expected_time = (average_times[0] + 1.5 * log2(problem_sizes[i]) * problem_sizes[i]);

        if (average_times[i] < 0.90 * expected_time || average_times[i] > 1.10 * expected_time) {
            fail_count++;
            if (fail_count > 1) {
                std::cout << "Less than " << average_times.size() - 2 << "/" << average_times.size() - 1 << " tests passed: ";
                return false;
            }
        }
        else {
            pass_count++;
        }
    }

    std::cout << pass_count << "/" << average_times.size() - 1 << " tests passed: ";

    for (int i = 0; i < average_times.size(); i++) {
        if (average_times[i] == -1)
            return false;
    }

    if (average_times.size() >= 2) {
        return true;
    }
    else 
        return false;
}

bool is_factorial(std::function<int(int)> f)
{
    std::cout << "Testing for O(n!):" << std::endl;

    cycle_count = 100;
    max_test_time = MAX_QUADRATIC_TEST_TIME;
    max_run_time = MAX_QUADRATIC_TEST_TIME;
    
    std::vector<int> problem_sizes = get_factorial_sizes();

    std::vector<double> average_times = get_average_times(f, problem_sizes);

    int fail_count = 0;
    int pass_count = 0;

    for (int i = 1; i < average_times.size(); i++) {
        double expected_time = average_times[i - 1] * fact(problem_sizes[i]) / fact(problem_sizes[i - 1]);

        if (average_times[i] < 0.80 * expected_time || average_times[i] > 1.20 * expected_time) {
            fail_count++;
            if (fail_count > 1) {
                std::cout << "Less than " << average_times.size() - 2 << "/" << average_times.size() - 1 << " tests passed: ";
                return false;
            }
        }
        else {
            pass_count++;
        }
    }

    std::cout << pass_count << "/" << average_times.size() - 1 << " tests passed: ";

    for (int i = 0; i < average_times.size(); i++) {
        if (average_times[i] == -1)
            return false;
    }

    if (average_times.size() >= 2) {
        return true;
    }
    else 
        return false;

    return true;
}

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

    if (print_test_results(is_constant(f), CONSTANT_NUM) == 0) return;
    if (print_test_results(is_logarithmic(f), LOGARITHMIC_NUM) == 0) return;
    if (print_test_results(is_linear(f), LINEAR_NUM) == 0) return;
    if (print_test_results(is_linearithmic(f), LINEARITHMIC_NUM) == 0) return;
    if (print_test_results(is_quadratic(f), QUADRATIC_NUM) == 0) return;
    if (print_test_results(is_factorial(f), FACTORIAL_NUM) == 0) return;
}
