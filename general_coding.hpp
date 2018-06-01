//
// Created by Erik Sevre on 5/31/18.
//

#pragma once

#include "type_definitions.hpp"
#include "thread_demo.hpp"

namespace ES {

    template <class VectorType>
    auto dot_product(const VectorType &a,
                     const VectorType &b,
                     ParallelPolicy policy)
    {
        switch (policy) {
            case ParallelPolicy::SEQ:
                return dot_product_one_thread(a, b);  // single thread
            case ParallelPolicy::PAR:
                return dot_product_two_thread(a, b);  // multi-threads
        }
    }

}