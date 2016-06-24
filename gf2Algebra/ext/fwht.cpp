/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "fwht.hpp"

namespace gf2Algebra {
namespace ext {



bool isPowerOfTwo(std::size_t number)
{
    return number > 0 && !(number & (number-1) );
}

std::size_t iLog2(std::size_t value)
{
    std::size_t log = 0;
    for(; value != 0; value >>= 1)
        ++log;

    return log-1;
}



} // ext namespace
} // gf2Algebra namespace
