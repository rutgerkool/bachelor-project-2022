#include "unit.hpp"

#define NRUNS_STANDARD              1000
#define NRUNS_LOGARITHMIC           1000000
#define NRUNS_CONSTANT              2000000
#define MAX_CONSTANT_TEST_TIME      10000
#define MAX_QUADRATIC_TEST_TIME     20000000


using namespace std;

int cycle_count = NRUNS_STANDARD;
int max_test_time = MAX_QUADRATIC_TEST_TIME;

enum big_o_category {
    CONSTANT = 0,
    LINEAR = 1,
    LOGARITHMIC,
    QUADRATIC = 2
};

vector<int> return_random_vector(int size) 
{
    vector<int> v(size);
    srand((unsigned)time(0)); 

    for (int i = 0; i < size; i++) {
        v[i] = rand() % size;
    }

    return v;
} 

double run_test_case(int x, function<int(int)> f) 
{
    auto t_start = chrono::high_resolution_clock::now();
    f(x);    
    auto t_end = chrono::high_resolution_clock::now();

    return chrono::duration<double, nano>(t_end-t_start).count();
}

vector<int> get_quadratic_sizes() 
{
    vector<int> problem_sizes{100};

    for (int i = 0; i < 5; i++) {
        problem_sizes.push_back(problem_sizes[i] * 2);
    }

    return problem_sizes;
}

vector<int> get_linear_sizes() 
{
    vector<int> problem_sizes{2000};

    for (int i = 0; i < 9; i++) {
        problem_sizes.push_back(problem_sizes[i] * 2);
    }

    return problem_sizes;
}

vector<int> get_logarithmic_sizes() 
{
    vector<int> problem_sizes{1, 10};

    for (int i = 2; i < 10; i++) {
        problem_sizes.push_back(pow(problem_sizes[1], i));
    }

    return problem_sizes;
}

double get_average_time(function<int(int)> f, int problem_size) 
{
    double average_time = 0;

    for (int j = 0; j < cycle_count; j++) {
        double time_taken = run_test_case(problem_size, f);
        average_time += time_taken;
    }

    average_time /= cycle_count;
    cout << "[Size: " << left << setw(10) << problem_size << "]";
    cout << fixed << setprecision(2) << "    Average time: " << average_time << " ns" << endl;

    if (average_time > max_test_time) {
        cout << "\nExecution aborted due to exceeding of maximum time: ";
        return -1;
    }

    return average_time;
}

vector<double> get_average_times(function<int(int)> f, vector<int> problem_sizes) 
{
    vector<double> average_times;
    for (int i = 0; i < problem_sizes.size(); i++) {
        double average_time = 0;
        
        average_time = get_average_time(f, problem_sizes[i]);
        if (average_time == - 1) {
            average_times.push_back(-1);
            return average_times;
        }
        average_times.push_back(average_time);
    }
    cout << endl;

    return average_times;
}

bool is_constant(function<int(int)> f)
{
    cycle_count = NRUNS_CONSTANT;
    max_test_time = MAX_CONSTANT_TEST_TIME;

    vector<int> problem_sizes = get_logarithmic_sizes();

    vector<double> average_times = get_average_times(f, problem_sizes);

    cycle_count = NRUNS_STANDARD;
    max_test_time = MAX_QUADRATIC_TEST_TIME;

    double expected_time = accumulate(average_times.begin(), average_times.end(), 0.0) / average_times.size();

    int fail_count = 0;
    int pass_count = 0;

    for (int i = 0; i < average_times.size(); i++) {

        if (average_times[i] < 0.97 * expected_time || average_times[i] > 1.03 * expected_time) {
            fail_count++;

            if (fail_count > 2)
                cout << "Less than " << average_times.size() - 2 << " tests passed: ";
                return false;
        }
        else {
            pass_count++;
        }
    }

    cout << pass_count << "/" << average_times.size() << " tests passed: ";

    for (int i = 0; i < average_times.size(); i++) {
        if (average_times[i] == -1)
            return false;
    }

    return true;
}

bool is_linear(function<int(int)> f)
{
    vector<int> problem_sizes = get_linear_sizes();

    vector<double> average_times = get_average_times(f, problem_sizes);
    
    int fail_count = 0;
    int pass_count = 0;

    for (int i = 0; i < average_times.size() - 1; i++) {
        double expected_time = 2 * average_times[i];
        
        if (average_times[i + 1] < 0.80 * expected_time || average_times[i + 1] > 1.20 * expected_time) {
            fail_count++;
            if (fail_count > 2) 
                cout << "Less than " << average_times.size() - 3 << " tests passed: ";
                return false;
        }
        else {
            pass_count++;
        }
    }

    cout << pass_count << "/" << average_times.size() - 1 << " tests passed: ";

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

bool is_quadratic(function<int(int)> f)
{
    vector<int> problem_sizes = get_quadratic_sizes();

    vector<double> average_times = get_average_times(f, problem_sizes);

    int fail_count = 0;
    int pass_count = 0;

    for (int i = 0; i < average_times.size() - 1; i++) {
        double expected_time = pow(2, static_cast<int>(QUADRATIC)) * average_times[i];

        if (average_times[i + 1] < 0.90 * expected_time || average_times[i + 1] > 1.10 * expected_time) {
            
            fail_count++;
            if (fail_count > 1) 
                cout << "Less than " << average_times.size() - 2 << " tests passed: ";
                return false;
        }
        else {
            pass_count++;
        }
    }

    cout << pass_count << "/" << average_times.size() - 1 << " tests passed: ";

    for (int i = 0; i < average_times.size(); i++) {
        if (average_times[i] == -1)
            return false;
    }

    return true;
}

bool is_logarithmic(function<int(int)> f)
{
    cycle_count = NRUNS_LOGARITHMIC;
    max_test_time = MAX_CONSTANT_TEST_TIME;
    
    vector<int> problem_sizes = get_logarithmic_sizes();

    vector<double> average_times = get_average_times(f, problem_sizes);

    cycle_count = NRUNS_STANDARD;
    max_test_time = MAX_QUADRATIC_TEST_TIME;

    int pass_count = 0;

    for (int i = 0; i < average_times.size() - 1; i++) {
        double expected_time = average_times[0] + log2(problem_sizes[i]);
        if (average_times[i + 1] < 0.90 * expected_time || average_times[i + 1] > 1.10 * expected_time) {
            return false;
        }
        else {
            pass_count++;
        }
    }

    cout << pass_count << "/" << average_times.size() - 1 << " tests passed: ";

    return true;
}

void run_all_test_cases(function<int(int)> f, const std::string& function_name) 
{
    cout << "\nTesting function " << function_name << endl << endl;

    cout << "Testing for O(1):" << endl;
    if (is_constant(f)) {
        cout << "\033[1;32mSUCCESS\033[0m" << endl;
        cout << "\nFunction is in O(1)\n" << endl;
        return;    
    }
    else {
        cout << "\033[1;31mFAIL\033[0m" << endl;
        cout << "\nFunction is not in O(1)\n" << endl; 
    }

    cout << "\nTesting for O(log(n)):" << endl;
    if (is_logarithmic(f)) {
        cout << "\033[1;32mSUCCESS\033[0m" << endl;
        cout << "\nFunction is in O(log(n))\n" << endl;
        return;    
    }
    else {
        cout << "\033[1;31mFAIL\033[0m" << endl;
        cout << "\nFunction is not in O(log(n))\n" << endl; 
    }
    
    cout << "\nTesting for O(n):" << endl;
    if (is_linear(f)) {
        cout << "\033[1;32mSUCCESS\033[0m" << endl;
        cout << "\nFunction is in O(n)\n" << endl;
        return;    
    }
    else {
        cout << "\033[1;31mFAIL\033[0m" << endl;
        cout << "\nFunction is not in O(n)\n" << endl; 
    }

    cout << "\nTesting for O(n^2):" << endl;
    if (is_quadratic(f)) {
        cout << "\033[1;32mSUCCESS\033[0m" << endl;
        cout << "\nFunction is in O(n^2)\n" << endl;
        return;
    }
    else {
        cout << "\033[1;31mFAIL\033[0m" << endl;
        cout << "\nFunction is not in O(n^2)\n" << endl;
    } 
}
