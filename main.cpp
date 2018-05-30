#include <iostream>
#include <vector>
#include <algorithm>

#include "thread_demo.hpp"


std::vector<double> gen_linspace(double start, double stop, size_t num) {
    std::vector<double> x(num);
    std::generate(x.begin(), x.end(),
                  [start, stop, i=0, dx=(stop - start)/(num-1.0)]() mutable
                  {
                      return start + dx*i++;
                  });
    return x;
}

void print(std::vector<double> vec) {
    for (const auto &v : vec) {
        std::cout << v << " ";
    }
    std::cout << "\n";
}

int main() {
    //
    //  Test to see how many threads are available for concurrency
    //
    int val = std::thread::hardware_concurrency();
    std::cout << "val: " << val << '\n';

    size_t sz = 1001;
    const ES::Vector v1 = gen_linspace(1, 10, sz);
    const ES::Vector v2 = gen_linspace(10, 1, sz);

    print(v1);
    print(v2);

    double dot_prod = ES::parallel_dot_product(v1, v2);

    std::cout << "Dot product: " << dot_prod << "\n";

}


