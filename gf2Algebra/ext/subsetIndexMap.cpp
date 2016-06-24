/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "subsetIndexMap.hpp"
#include <limits>
#include <cassert>

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

SubsetIndexMap::SubsetIndexMap()
    : lst_(1, MaskAndShift())
{
}

SubsetIndexMap::SubsetIndexMap(const std::bitset<MAX_K_VALUE> & usedBits)
{
    initializeShiftMap(usedBits);
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

    // check if the index is correct
    assert(fromIndex(idx) == value);

    return idx;
}

void SubsetIndexMap::initializeShiftMap(const std::bitset<MAX_K_VALUE> &usedBits)
{
    unsigned char noOfActiveBits = 0;

    std::size_t curBit = 0;
    while(curBit < MAX_K_VALUE)
    {
        // find the first set bit
        while(curBit < MAX_K_VALUE && usedBits[curBit] == false)
            ++curBit;

        // all bits processed? if so, we are finished
        if(curBit == MAX_K_VALUE)
            return;

        std::size_t firstActive = curBit;

        // find the first non-set bit
        while(curBit < MAX_K_VALUE && usedBits[curBit] == true)
            ++curBit;

        std::size_t lastActive = curBit;

        // make the mask and shift
        unsigned char shift = firstActive - noOfActiveBits;
        std::size_t noBits = lastActive - firstActive;
        Z2k::storage_type mask = ((1 << noBits) - 1) << noOfActiveBits;

        // and add it
        lst_.push_back(MaskAndShift(mask, shift));

        // and update the number of bits
        noOfActiveBits += noBits;
    }
}


} // namespace gf2Algebra
