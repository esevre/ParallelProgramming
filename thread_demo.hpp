//
// Created by Erik Sevre on 5/29/18.
//
//  The code below is intended for an example of code with threads,
//  how to organize code for different situations. This is not optimized
//  to be fast, just to show how code can be organized.
//

#pragma once


#include <iostream>
#include <thread>
#include <vector>

#include <algorithm>
#include <numeric>

#include "type_definitions.hpp"


namespace ES{

    /// Function to generate a vector of linearly spaced points.
    /// This function will generate _num_ points that start at the value _start_ and stop at the value _stop_
    /// \param start starting value for array of points
    /// \param stop last value of the array of points
    /// \param num number of points to generate
    /// \return Vector containing linearly spaced points
    ///
    Vector gen_linspace(const NumberType start,
                        const NumberType stop,
                        const size_t num)
    {
        Vector x(num);
        std::generate(x.begin(), x.end(),
                      [start, stop, i=0, dx=(stop - start) / (num-1.0)]() mutable
                      {
                          return start + dx*i++;
                      });
        return x;
    }

    ///    Compute the dot-product for non-adjacent data seperated by a stride length.
    ///  For two vectors, the user will input the stripe,
    ///  and the number of stripes in total to determine the stride.
    ///
    /// \Example
    /// So for 4 stripes this will look at elts in multiples of 4, i.e.: <br>
    ///    0, 4,  8, ... <br>
    ///    1, 5,  9, ... <br>
    ///    2, 6, 10, ... <br>
    ///    3, 7, 11, ...
    ///
    /// \param a first input vector
    /// \param b second input vector
    /// \param stripe_num the index of the first value in the desired stripe
    /// \param num_stripes the stride for
    /// \return
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

    //    ****    ****    ****    ****    ****    ****    ****
    //  Hard coded functions for 1, 2, 3, and 4 threads
    //    ****    ****    ****    ****    ****    ****    ****
    NumberType dot_product_one_thread(const Vector &a,
                                      const Vector &b)
    {
        NumberType value0 = 0;

        std::thread t0(product_thread, std::ref(value0), std::ref(a), std::ref(b), 0, 1);
        t0.join();

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

    /// Simple parallel partial dot product function.
    /// Computation starts at the index indicated by start,
    /// and finishes at the index indicated by stop.
    /// Return value is passes as a parameter for simplifying use with std::thread
    ///
    /// \param a  vector input
    /// \param b  vector input
    /// \param start starting index
    /// \param stop  stopping index (not included in product)
    /// \param value return value stored here
    void parallel_partial_product(const Vector &a,
                                  const Vector &b,
                                  const size_t start,
                                  const size_t stop,
                                  NumberType &value)
    {
        value = std::inner_product(std::cbegin(a) + start,
                                   std::cbegin(a) + stop,
                                   std::cbegin(b) + start,
                                   static_cast<NumberType>(0));
    }


    /// Simple method to compute dot product with parallel programming.
    /// Here I am using threads, but this could be updated for OpenMP or MPI
    ///
    /// \param a [Vector] input
    /// \param b [Vector] input
    /// \return [double] dot product value
    NumberType parallel_dot_product(const Vector &a,
                                    const Vector &b)
    {
        const int num_threads = std::thread::hardware_concurrency();
        std::vector<std::thread> thread_list((unsigned long)num_threads);
        std::vector<NumberType> values((unsigned long)num_threads);

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

        return std::accumulate(std::cbegin(values),
                               std::cend(values),
                               static_cast<NumberType>(0));
    }

    /// Simple implementation of sequential dot product.
    /// This function just calls the inner_product function
    /// defined in the STL numeric header files
    ///
    /// \param a [Vector] input
    /// \param b [Vector] input
    /// \return [double] dot product value
    NumberType sequential_dot_product(const Vector &a,
                                      const Vector &b)
    {
        return std::inner_product(a.cbegin(),
                                  a.cend(),
                                  b.cbegin(),
                                  static_cast<NumberType>(0));
    }
}


