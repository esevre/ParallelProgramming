//
// Created by Erik Sevre on 5/30/18.
//

#pragma once

#include <vector>

namespace ES {
    //
    //  Here I define the types I am using.
    //  I define the types here so that I can change all the types
    //    in all my code by editing a few lines here.
    //
    //  This also simplifies code to be more readable:
    //    std::vector<NumberType> --> Vector (shorter and nicer)
    //
    //  Sometimes types in C++ can get very long,
    //
    using NumberType = float;
    using Vector = std::vector<NumberType>;

    enum class ParallelPolicy { SEQ, PAR };

}