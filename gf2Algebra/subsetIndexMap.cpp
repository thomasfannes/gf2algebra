/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "subsetIndexMap.hpp"
#include <limits>

namespace gf2Algebra {


SubsetIndexMap::SubsetIndexMap()
    : lst_(1, MaskAndShift())
{
}

SubsetIndexMap::SubsetIndexMap(unsigned char k, const std::set<unsigned char> & unusedBits)
{
    initializeShiftMap(k, unusedBits);
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

void SubsetIndexMap::initializeShiftMap(unsigned char k, const std::set<unsigned char> & unusedBits)
{

}

struct SubsetIndexMap::MaskAndShift
{
    MaskAndShift()
        : mask(std::numeric_limits<Z2k::storage_type>::max()), shift(0)
    {
    }

    Z2k::storage_type mask;
    unsigned char shift;
};

} // namespace gf2Algebra
