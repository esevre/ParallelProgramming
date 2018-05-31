#include <iostream>
#include <vector>
#include <algorithm>

#include "thread_demo.hpp"
#include "benchmarking_runs.hpp"


int main() {
    //
    //  Test to see how many threads are available for concurrency
    //
    int val = std::thread::hardware_concurrency();
    std::cout << "val: " << val << '\n';

    //
    //  Thread runs
    //
    ES::benchmark_one_thread(10'000'000);
    ES::benchmark_two_thread(10'000'000);
    ES::benchmark_three_thread(10'000'000);
    ES::benchmark_four_thread(10'000'000);

}


