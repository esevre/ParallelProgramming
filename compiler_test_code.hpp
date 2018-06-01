//
// Created by Erik Sevre on 5/31/18.
//

#pragma once


#include <array>
#include <vector>
#include <numeric>
#include <algorithm>

// using an anonomous namespace can reduce code in the binary
// since functions defined here are only available to this file at compile time
namespace {

    template <int NUM>
    constexpr
    auto linspace(const double start,
                  const double stop) -> std::array<double, NUM>
    {
        std::array<double, NUM> a;
        double dx = (stop-start)/(NUM-1.0);
        for (int i = 0; i < NUM; ++i){
            a[i] = start + dx*i;
        }
        return a;
    }

    template <int NUM>
    constexpr
    double dot_product_seq(const std::array<double, NUM> &a,
                           const std::array<double, NUM> &b)
    {
        double dot_product = 0.0;
        for (int i = 0; i < NUM; ++i) {
            dot_product += a[i] * b[i];
        }

        return dot_product;
    }

    constexpr
    int compiler_explorer_code() {
        const size_t sz = 100000;
        const std::array<double, sz> a1 = linspace<sz>(0, 1);
        const std::array<double, sz> a2 = linspace<sz>(1, 0);

        const double dotProduct = dot_product_seq<sz>(a1, a2) / (double)sz;

        int num = 0;
        if (dotProduct < 0.15) {
            num = 1;
        } else if (dotProduct < 0.25) {
            num = 2;  // this value should be returned ^^
        } else {
            num = 3;
        }

        return num;
    }
}
