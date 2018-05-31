//
// Created by Erik Sevre on 5/30/18.
//

#pragma once

#include <chrono>


#include "thread_demo.hpp"


namespace ES{

    void benchmark_parallel(const size_t sz = 10001) {
        //std::chrono::high_resolution_clock::time_point start, stop;
        auto start = std::chrono::system_clock::now();

        const ES::Vector v1 = gen_linspace(0, 10, sz);
        const ES::Vector v2 = gen_linspace(10, 0, sz);

        double dot_prod = ES::parallel_dot_product(v1, v2);


        auto stop = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

        std::cout << "Parallel computation took: " << duration << std::endl;


    }

    void benchmark_sequential(const size_t sz = 10001) {
        //std::chrono::high_resolution_clock::time_point start, stop;
        auto start = std::chrono::system_clock::now();

        const ES::Vector v1 = gen_linspace(0, 10, sz);
        const ES::Vector v2 = gen_linspace(10, 0, sz);

        double dot_prod = ES::sequential_dot_product(v1, v2);


        auto stop = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

        std::cout << "Sequential computation took: " << duration << std::endl;
    }

    void benchmark_one_thread(const size_t sz = 10001) {
        //std::chrono::high_resolution_clock::time_point start, stop;
        auto start = std::chrono::system_clock::now();

        const ES::Vector v1 = gen_linspace(0, 10, sz);
        const ES::Vector v2 = gen_linspace(10, 0, sz);

        double dot_prod = ES::dot_product_one_thread(v1, v2);


        auto stop = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

        std::cout << "One Thread computation took: " << duration << std::endl;
    }

    void benchmark_two_thread(const size_t sz = 10001) {
        //std::chrono::high_resolution_clock::time_point start, stop;
        auto start = std::chrono::system_clock::now();

        const ES::Vector v1 = gen_linspace(0, 10, sz);
        const ES::Vector v2 = gen_linspace(10, 0, sz);

        double dot_prod = ES::dot_product_two_thread(v1, v2);


        auto stop = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

        std::cout << "Two Thread computation took: " << duration << std::endl;
    }

    void benchmark_three_thread(const size_t sz = 10001) {
        //std::chrono::high_resolution_clock::time_point start, stop;
        auto start = std::chrono::system_clock::now();

        const ES::Vector v1 = gen_linspace(0, 10, sz);
        const ES::Vector v2 = gen_linspace(10, 0, sz);

        double dot_prod = ES::dot_product_three_thread(v1, v2);


        auto stop = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

        std::cout << "Three Thread computation took: " << duration << std::endl;
    }

    void benchmark_four_thread(const size_t sz = 10001) {
        //std::chrono::high_resolution_clock::time_point start, stop;
        auto start = std::chrono::system_clock::now();

        const ES::Vector v1 = gen_linspace(0, 10, sz);
        const ES::Vector v2 = gen_linspace(10, 0, sz);

        double dot_prod = ES::dot_product_four_thread(v1, v2);


        auto stop = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

        std::cout << "Four Thread computation took: " << duration << std::endl;
    }

}
