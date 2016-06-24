/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_IDENTITYINDEXMAP_HPP
#define GF2ALGEBRA_EXT_IDENTITYINDEXMAP_HPP

#include "../config.hpp"

namespace gf2Algebra {
namespace ext {

struct IdentityIndexMap
{
    IdentityIndexMap() {}
    explicit IdentityIndexMap(const Bitset & /*activeBits*/) {}

    Z2k fromIndex(std::size_t idx) const          { return Z2k(idx); }
    std::size_t fromGroupValue(Z2k value) const   { return value.getValue(); }
};

} // ext namespace
} // gf2Algebra namespace

#endif // GF2ALGEBRA_EXT_IDENTITYINDEXMAP_HPP
