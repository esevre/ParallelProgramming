#include <iostream>
#include <vector>
#include <algorithm>

#include "thread_demo.hpp"
#include "benchmarking_runs.hpp"
#include "general_coding.hpp"

#include "compiler_test_code.hpp"

int main() {
    //
    //  Test to see how many threads are available for concurrency
    //
    int num_threads = std::thread::hardware_concurrency();
    std::cout << "Number of threads: " << num_threads << '\n';

    const int sz = 1001;

    ES::Vector v1 = ES::gen_linspace(0, 1, sz);
    ES::Vector v2 = ES::gen_linspace(1, 0, sz);

    auto dot_prod_seq = ES::dot_product(v1, v2, ES::ParallelPolicy::SEQ);
    auto dot_prod_par = ES::dot_product(v1, v2, ES::ParallelPolicy::PAR);

    std::cout << "difference in dot products: " << (dot_prod_seq - dot_prod_par) << "\n";

    double val = 0;

    // 1000 is chosen as an example threshold for when to switch to parallel execution
    if (v1.size() < 1000) {
        std::cout << "small run\n";
        val = ES::dot_product(v1, v2, ES::ParallelPolicy::SEQ);
    } else {
        std::cout << "big run\n";
        val = ES::dot_product(v1, v2, ES::ParallelPolicy::PAR);
    }

    std::cout << "dot product is: " << val << "\n";

    //
    //  Thread runs
    //
    ES::benchmark_one_thread(1'000'000);
    ES::benchmark_two_thread(1'000'000);
    ES::benchmark_three_thread(1'000'000);
    ES::benchmark_four_thread(1'000'000);


    return compiler_explorer_code();
}


