#include "unit.hpp"

#define NRUNS_STANDARD              500
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

#define TEST_CASE(f, i, tests) { \
    if (f == -1) { \
        cout << "FAIL: "<< __FUNCTION__ << " failed at size " << tests[i] << endl; \
        } \
    else { \
        cout << "Test " << i + 1 << "/" << tests.size() << ": " << "SUCCESS" << endl; \
    } \
}


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

    for (int el : problem_sizes) cout << el << endl;

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
    cout << fixed << setprecision(2) << "Average time: " << average_time << endl;

    if (average_time > max_test_time) {
        cout << "timeout\n";
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

    for (int i = 0; i < average_times.size(); i++) {

        if (average_times[i] < 0.97 * expected_time || average_times[i] > 1.03 * expected_time) {
            cout << "Does not pass test" << endl;
            fail_count++;

            if (fail_count > 2)
                return false;
        }
        else {
            cout << "Passes test" << endl;
        }
    }

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

    for (int i = 0; i < average_times.size() - 1; i++) {
        double expected_time = 2 * average_times[i];
        
        if (average_times[i + 1] < 0.80 * expected_time || average_times[i + 1] > 1.20 * expected_time) {
            cout << "Does not pass test" << endl;
            fail_count++;
            if (fail_count > 2) 
                return false;
        }
        else {
            cout << "Passes test" << endl;
        }
    }

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

    for (int i = 0; i < average_times.size() - 1; i++) {
        double expected_time = pow(2, static_cast<int>(QUADRATIC)) * average_times[i];

        if (average_times[i + 1] < 0.90 * expected_time || average_times[i + 1] > 1.10 * expected_time) {
            cout << "Does not pass test" << endl;
            
            fail_count++;
            if (fail_count > 1) 
                return false;
        }
        else {
            cout << "Passes test" << endl;
        }
    }

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

    for (int i = 0; i < average_times.size() - 1; i++) {
        double expected_time = average_times[0] + log2(problem_sizes[i]);
        if (average_times[i + 1] < 0.90 * expected_time || average_times[i + 1] > 1.10 * expected_time) {
            cout << "Does not pass test" << endl;
            return false;
        }
        else {
            cout << "Passes test" << endl;
        }
    }

    return true;
}

void run_all_test_cases(function<int(int)> f) 
{
    
    cout << "Testing constant" << endl;
    if (is_constant(f)) {
        cout << "Function is constant\n" << endl;
        return;    
    }
    else cout << "Function is not constant\n" << endl; 
    
    cout << "Testing linear" << endl;
    if (is_linear(f)) {
        cout << "Function is linear\n" << endl;
        return;    
    }
    else cout << "Function is not linear\n" << endl; 

    cout << "Testing logarithmic" << endl;
    if (is_logarithmic(f)) {
        cout << "Function is logarithmic\n" << endl;
        return;    
    }
    else cout << "Function is not logarithmic\n" << endl; 

    if (is_quadratic(f)) {
        cout << "Function is quadratic\n" << endl;
        return;
    }
    else cout << "Function is not quadratic\n" << endl; 
}

void run_all_test_cases(function<int(vector<int>)> f) 
{
    vector<int> problem_sizes{1, 10, 100, 1000, 10000, 100000, 1000000};

    for (int i = 0; i < problem_sizes.size(); i++) {
        vector<int> v = return_random_vector(problem_sizes[i]);

        TEST_CASE(f(v), i, problem_sizes);
    }
}

/*



*/
