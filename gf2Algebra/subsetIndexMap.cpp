/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "subsetIndexMap.hpp"
#include <limits>

namespace gf2Algebra {


MaskAndShift::MaskAndShift()
    : mask(std::numeric_limits<Z2k::storage_type>::max()), shift(0)
{
}

MaskAndShift::MaskAndShift(Z2k::storage_type nMask, unsigned char nShift)
    : mask(nMask),
      shift(nShift)
{
}

void swap(MaskAndShift & lhs, MaskAndShift & rhs)
{
    using std::swap;
    swap(lhs.mask, rhs.mask);
    swap(lhs.shift, rhs.shift);
}


SubsetIndexMap::SubsetIndexMap()
    : lst_(1, MaskAndShift())
{
}

SubsetIndexMap::SubsetIndexMap(const SubsetIndexMap & rhs)
    : lst_(rhs.lst_)
{
}

SubsetIndexMap::SubsetIndexMap(unsigned char k, const std::bitset<MAX_K_VALUE> & usedBits)
{
    initializeShiftMap(k, usedBits);
}

SubsetIndexMap & SubsetIndexMap::operator=(const SubsetIndexMap & rhs)
{
    SubsetIndexMap tmp(rhs);
    swap(tmp, *this);

    return *this;
}

Z2k SubsetIndexMap::fromIndex(std::size_t idx) const
{
    Z2k::storage_type value = 0;

    for(std::size_t i = 0; i < lst_.size(); ++i)
    {
        const MaskAndShift & cur = lst_[i];
        value |= (idx & cur.mask) << cur.shift;
    }

    return Z2k(value);
}

std::size_t SubsetIndexMap::fromGroupValue(Z2k value) const
{
    std::size_t idx = 0;
    Z2k::storage_type tp = value.getValue();

    for(std::size_t i = 0; i < lst_.size(); ++i)
    {
        const MaskAndShift & cur = lst_[i];
        idx |= (tp >> cur.shift) & cur.mask;
    }

    return idx;
}

void SubsetIndexMap::initializeShiftMap(unsigned char k, const std::bitset<MAX_K_VALUE> &usedBits)
{


    unsigned char noOfActiveBits = 0;

    std::size_t curBit = 0;
    while(curBit < MAX_K_VALUE)
    {
        // find the first set bit
        while(curBit < k && usedBits[curBit] == false)
            ++curBit;

        // all bits processed? if so, we are finished
        if(curBit == k)
            return;

        std::size_t firstActive = curBit;

        // find the first non-set bit
        while(curBit < k && usedBits[curBit] == true)
            ++curBit;

        std::size_t lastActive = curBit;

        // make the mask and shift
        unsigned char shift = firstActive - noOfActiveBits;
        std::size_t noBits = lastActive - firstActive;
        Z2k::storage_type mask = ((1 << noBits) - 1) << shift;

        // and add it
        lst_.push_back(MaskAndShift(mask, shift));

        // and update the number of bits
        noOfActiveBits += noBits;
    }
}

void swap(SubsetIndexMap & lhs, SubsetIndexMap & rhs)
{
    using std::swap;
    swap(lhs.lst_, rhs.lst_);
}


} // namespace gf2Algebra
