/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_FWHT_HXX
#define GF2ALGEBRA_EXT_FWHT_HXX

#include "fwht.hpp"
#include <iostream>
#include <cassert>

namespace gf2Algebra {
namespace ext {
namespace internal {

template <typename DataType>
void fwht_radix2(std::vector<DataType> & elements, std::size_t firstPosition, std::size_t size)
{
    DataType t = elements[firstPosition];
    elements[firstPosition] = t + elements[firstPosition + size];
    elements[firstPosition + size] = t - elements[firstPosition + size];
}

template <typename DataType>
void fwht_radix4(std::vector<DataType> & elements, std::size_t firstPosition, std::size_t size)
{
    std::size_t p1 = firstPosition;
    std::size_t p2 = firstPosition | size;
    std::size_t p3 = firstPosition | (size << 1);
    std::size_t p4 = p3 | size;

    // get the intermediate result
    DataType ap = elements[p1] + elements[p3];
    DataType bp = elements[p2] + elements[p4];
    DataType cp = elements[p1] - elements[p3];
    DataType dp = elements[p2] - elements[p4];

    elements[p1] = ap + bp;
    elements[p2] = ap - bp;
    elements[p3] = cp + dp;
    elements[p4] = cp - dp;
}



bool isPowerOfTwo(std::size_t number);
std::size_t iLog2(std::size_t value);

template <typename DataType>
void int_fwht_4(std::vector<DataType> & elements, std::size_t k, std::size_t pos)
{
    std::size_t sz = (1 << k);
    std::size_t small_distance = (1 << (k-2));
    std::size_t large_distance = (1 << k);

    for(std::size_t step = 0; step < k; step+=2)
    {
        for(std::size_t offset = 0; offset < sz; offset += large_distance)
            for(std::size_t l = 0; l < small_distance; ++l)
                internal::fwht_radix4(elements, pos + offset + l, small_distance);

        small_distance >>= 2;
        large_distance >>= 2;
    }
}

template <typename DataType>
void int_fwht_odd_k(std::vector<DataType> & elements, std::size_t k)
{
    std::size_t small_distance = (1 << (k-1));
    for(std::size_t l = 0; l < small_distance; ++l)
        internal::fwht_radix2(elements, l, small_distance);
}


} // internal namespace


template <typename DataType>
void old_fwht(std::vector<DataType> & elements, std::size_t k)
{
    std::size_t sz = elements.size();
    assert(sz == (1 << k));

    std::size_t small_distance = (1 << (k-1));
    std::size_t large_distance = (1 << k);


    for(std::size_t step = 0; step < k; ++step)
    {
        for(std::size_t offset = 0; offset < sz; offset += large_distance)
            for(std::size_t l = 0; l < small_distance; ++l)
                internal::fwht_radix2(elements, offset + l, small_distance);

        small_distance >>= 1;
        large_distance >>= 1;
    }
}


template <typename DataType>
void fwht(std::vector<DataType> & elements, std::size_t k)
{
    std::size_t sz = elements.size();
    assert(sz == (1 << k));


    if((k&1) == 0)
        internal::int_fwht_4(elements, k, 0);
    else
    {
        internal::int_fwht_odd_k(elements, k);
        internal::int_fwht_4(elements, k-1, 0);
        internal::int_fwht_4(elements, k-1, sz >> 1);
    }
}

template <typename DataType>
void fwht(std::vector<DataType> & elements)
{
    std::size_t sz = elements.size();
    assert(internal::isPowerOfTwo(sz));
    fwht(elements, internal::iLog2(sz));
}

} // ext namespace
} // namespace gf2Algebra


#endif // GF2ALGEBRA_EXT_FWHT_HXX
