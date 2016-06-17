/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_INTERNAL_FWHT_HXX
#define GF2ALGEBRA_INTERNAL_FWHT_HXX

#include "fwht.hpp"
#include <iostream>
#include <cassert>

namespace gf2Algebra {
namespace internal {


template <typename DataType>
void fwht_radix2(std::vector<DataType> & elements, std::size_t firstPosition, std::size_t size)
{
    DataType t = elements[firstPosition];
    elements[firstPosition] = t + elements[firstPosition + size];
    elements[firstPosition + size] = t - elements[firstPosition + size];
}

template <typename DataType>
void fwht(std::vector<DataType> & elements, std::size_t k)
{
    std::size_t sz = elements.size();
    assert(sz == (1 << k));

    std::size_t small_distance = (1 << (k-1));
    std::size_t large_distance = (1 << k);


    for(std::size_t step = 0; step < k; ++step)
    {
        for(std::size_t offset = 0; offset < sz; offset += large_distance)
            for(std::size_t l = 0; l < small_distance; ++l)
                fwht_radix2(elements, offset + l, small_distance);

        small_distance >>= 1;
        large_distance >>= 1;
    }
}

template <typename DataType>
void fwht(std::vector<DataType> & elements)
{
    std::size_t sz = elements.size();
    assert(isPowerOfTwo(sz));
    fwht(elements, iLog2(sz));
}

} // internal namespace
} // namespace gf2Algebra


#endif // GF2ALGEBRA_INTERNAL_FWHT_HXX
