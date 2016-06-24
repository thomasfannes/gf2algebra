/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_INTERNAL_VALUECOEFFICIENTPAIR_HPP
#define GF2ALGEBRA_EXT_INTERNAL_VALUECOEFFICIENTPAIR_HPP

#include "../../config.hpp"

namespace gf2Algebra {
namespace ext {
namespace internal {


class ValueCoefficientPair
{
public:
    typedef GaloisField             field_type;
    typedef Z2k                     group_type;

    ValueCoefficientPair();
    ValueCoefficientPair(group_type val, field_type coeff);

    group_type value;
    field_type coefficient;
};

void swap(ValueCoefficientPair & lhs, ValueCoefficientPair & rhs);

// operators
ValueCoefficientPair & operator+=(ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs);
ValueCoefficientPair operator+(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs);
ValueCoefficientPair operator*(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs);
bool operator==(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs);
bool operator!=(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs);
bool operator<(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs);

} // internal namespace
} // ext namespace
} // gf2Algebra namespace

#include "valueCoefficientPair.hxx"

#endif // GF2ALGEBRA_EXT_INTERNAL_VALUECOEFFICIENTPAIR_HPP
