/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_SUBSETINDEXMAP_HPP
#define GF2ALGEBRA_SUBSETINDEXMAP_HPP

#include <bitset>
#include <vector>
#include "../config.hpp"

namespace gf2Algebra {

struct MaskAndShift
{
    MaskAndShift(Z2k::storage_type nMask, unsigned char nShift);
    MaskAndShift();
    friend void swap(MaskAndShift & lhs, MaskAndShift & rhs);

    Z2k::storage_type mask;
    unsigned char shift;
};

class SubsetIndexMap
{
public:
    SubsetIndexMap();
    SubsetIndexMap(const std::bitset<MAX_K_VALUE> & usedBits);

    Z2k fromIndex(std::size_t idx) const;
    std::size_t fromGroupValue(Z2k value) const;

private:
    void initializeShiftMap(const std::bitset<MAX_K_VALUE> & usedBits);

    std::vector<MaskAndShift> lst_;
};

} // namespace gf2Algebra

#endif // GF2ALGEBRA_SUBSETINDEXMAP_HPP
