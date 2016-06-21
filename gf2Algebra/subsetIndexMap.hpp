/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_SUBSETINDEXMAP_HPP
#define GF2ALGEBRA_SUBSETINDEXMAP_HPP

#include <bitset>
#include <vector>
#include "z2k.hpp"

namespace gf2Algebra {

class SubsetIndexMap
{
    struct MaskAndShift;

public:
    SubsetIndexMap();
    SubsetIndexMap(unsigned char k, const std::bitset<MAX_K_VALUE> & usedBits);
    SubsetIndexMap(const SubsetIndexMap & rhs);

    SubsetIndexMap & operator=(const SubsetIndexMap & rhs);

    Z2k fromIndex(std::size_t idx) const;
    std::size_t fromGroupValue(Z2k value) const;

private:
    friend void swap(SubsetIndexMap & lhs, SubsetIndexMap & rhs);

    void initializeShiftMap(unsigned char k, const std::bitset<MAX_K_VALUE> & usedBits);

    std::vector<MaskAndShift> lst_;
};

} // namespace gf2Algebra

#endif // GF2ALGEBRA_SUBSETINDEXMAP_HPP
