/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_INTERNAL_MASKFUNCTORS_HPP
#define GF2ALGEBRA_EXT_INTERNAL_MASKFUNCTORS_HPP

#include "valueCoefficientPair.hpp"

namespace gf2Algebra {
namespace ext {
namespace internal {

template <typename Function>
struct Z2kMaskFunctor : public Function
{
    Z2kMaskFunctor(Z2k::storage_type nMask, const Function & f) : Function(f), mask(nMask) {}
    void operator()(const ValueCoefficientPair & vcp) const { Function::operator()(ValueCoefficientPair(Z2k(vcp.value.getValue() & mask), vcp.coefficient)); }

    Z2k::storage_type mask;
};

template <typename Function>
Z2kMaskFunctor<Function> make_mask_function(Z2k::storage_type mask, const Function & function = Function())
{
    return Z2kMaskFunctor<Function>(mask, function);
}

} // internal namespace
} // ext namespace
} // gf2Algebra namespace

#endif // GF2ALGEBRA_EXT_INTERNAL_MASKFUNCTORS_HPP
