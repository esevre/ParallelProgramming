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


// todo: add timings

namespace ES{
    Vector gen_linspace(const NumberType start,
                        const NumberType stop,
                        const size_t num)
    {
        Vector x(num);
        std::generate(x.begin(), x.end(),
                      [start, stop, i=0, dx=(stop - start)/(num-1.0)]() mutable
                      {
                          return start + dx*i++;
                      });
        return x;
    }

    NumberType stripped_dot_product(const Vector &a,
                                    const Vector &b,
                                    const int stripe_num,
                                    const int num_stripes = 4)
    {
        NumberType dot_product = 0.0;
        for (int i = stripe_num; i < a.size(); i+=num_stripes) {
            dot_product += a[i]*b[i];
        }
        return dot_product;
    }

    void product_thread(NumberType &value,
                        const Vector &a,
                        const Vector &b,
                        const int stripe_num,
                        const int num_stripes = 4)
    {
        value = stripped_dot_product(a,b,stripe_num, num_stripes);
    }

    NumberType dot_product_one_thread(const Vector &a,
                                      const Vector &b)
    {
        NumberType value0 = 0;

        std::thread t0(product_thread, std::ref(value0), std::ref(a), std::ref(b), 0, 1);
        t0.join();
//        std::thread t1(product_thread, std::ref(value1), std::ref(a), std::ref(b), 1);
//        t1.join();
//        std::thread t2(product_thread, std::ref(value2), std::ref(a), std::ref(b), 2);
//        t2.join();
//        std::thread t3(product_thread, std::ref(value3), std::ref(a), std::ref(b), 3);
//        t3.join();

        return value0;
    }

    NumberType dot_product_two_thread(const Vector &a,
                                      const Vector &b)
    {
        NumberType value0 = 0;
        NumberType value1 = 0;

        std::thread t0(product_thread, std::ref(value0), std::ref(a), std::ref(b), 0, 2);
        std::thread t1(product_thread, std::ref(value1), std::ref(a), std::ref(b), 1, 2);
        t0.join();
        t1.join();

//        std::thread t2(product_thread, std::ref(value2), std::ref(a), std::ref(b), 2);
//        t2.join();
//        std::thread t3(product_thread, std::ref(value3), std::ref(a), std::ref(b), 3);
//        t3.join();

        return value0 + value1;
    }

    NumberType dot_product_three_thread(const Vector &a,
                                        const Vector &b)
    {
        NumberType value0 = 0;
        NumberType value1 = 0;
        NumberType value2 = 0;


        std::thread t0(product_thread, std::ref(value0), std::ref(a), std::ref(b), 0, 3);
        std::thread t1(product_thread, std::ref(value1), std::ref(a), std::ref(b), 1, 3);
        std::thread t2(product_thread, std::ref(value2), std::ref(a), std::ref(b), 2, 3);

        t0.join();
        t1.join();
        t2.join();


        return value0 + value1 + value2;
    }

    NumberType dot_product_four_thread(const Vector &a,
                                       const Vector &b)
    {
        NumberType value0 = 0;
        NumberType value1 = 0;
        NumberType value2 = 0;
        NumberType value3 = 0;

        std::thread t0(product_thread, std::ref(value0), std::ref(a), std::ref(b), 0, 4);
        std::thread t1(product_thread, std::ref(value1), std::ref(a), std::ref(b), 1, 4);
        std::thread t2(product_thread, std::ref(value2), std::ref(a), std::ref(b), 2, 4);
        std::thread t3(product_thread, std::ref(value3), std::ref(a), std::ref(b), 3, 4);

        t0.join();
        t1.join();
        t2.join();
        t3.join();

        return value0 + value1 + value2 + value3;
    }


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



    NumberType parallel_dot_product(const Vector &a,
                                    const Vector &b)
    {
        const int num_threads = std::thread::hardware_concurrency();
        std::vector<std::thread> thread_list((unsigned long)num_threads);
        std::vector<double> values((unsigned long)num_threads);

        for (int i = 0; i < num_threads; ++i) {
            size_t start = i*a.size() / num_threads;
            size_t stop = (i+1)*a.size() / num_threads;
            if (stop >= a.size()) { stop = a.size(); }
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

    NumberType sequential_dot_product(const Vector &a,
                                      const Vector &b)
    {
        return std::inner_product(a.cbegin(), a.cend(), b.cbegin(), 0.0);
    }
}


