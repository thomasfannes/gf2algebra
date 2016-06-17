/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_IDENTITYINDEXMAP_HPP
#define GF2ALGEBRA_IDENTITYINDEXMAP_HPP

#include "config.hpp"
#include "z2k.hpp"

namespace gf2Algebra {

struct IdentityIndexMap
{
    Z2k fromIndex(std::size_t idx) const          { return Z2k(idx); }
    std::size_t fromGroupValue(Z2k value) const   { return value.getValue(); }
};

} // gf2Algebra namespace

#endif // GF2ALGEBRA_IDENTITYINDEXMAP_HPP
