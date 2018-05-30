//
// Created by Erik Sevre on 5/29/18.
//

#pragma once


#include <iostream>
#include <thread>
#include <vector>

#include <algorithm>
#include <numeric>

#include "parallel_examples.hpp"


namespace ES{


    void parallel_partial_product(const Vector &a,
                                  const Vector &b,
                                  const size_t start,
                                  const size_t stop,
                                  NumberType &value)
    {
        value = std::inner_product(std::cbegin(a) + start,
                                   std::cbegin(a) + stop,
                                   std::cbegin(b) + start,
                                   0.0);
    }



    NumberType parallel_dot_product(const Vector &a, const Vector &b)
    {
        const int num_threads = std::thread::hardware_concurrency();
        std::vector<std::thread> thread_list((unsigned long)num_threads);
        std::vector<double> values((unsigned long)num_threads);

        for (int i = 0; i < num_threads; ++i) {
            size_t start = i*a.size() / num_threads;
            size_t stop = (i+1)*a.size() / num_threads;
            thread_list[i] = std::thread(parallel_partial_product,
                                         std::ref(a),
                                         std::ref(b),
                                         start,
                                         stop,
                                         std::ref(values[i]));
        }

        for (int i = 0; i < num_threads; ++i) {
            thread_list[i].join();
        }

        return std::accumulate(std::cbegin(values), std::cend(values), 0.0);
    }


}


