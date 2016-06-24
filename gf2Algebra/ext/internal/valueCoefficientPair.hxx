/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_INTERNAL_VALUECOEFFICIENTPAIR_HXX
#define GF2ALGEBRA_EXT_INTERNAL_VALUECOEFFICIENTPAIR_HXX

#include "valueCoefficientPair.hpp"
#include <cassert>

namespace gf2Algebra {
namespace ext {
namespace internal {



inline ValueCoefficientPair::ValueCoefficientPair()
    : value(group_type()),
      coefficient(field_type::zero)
{
}

inline ValueCoefficientPair::ValueCoefficientPair(group_type val, field_type coeff)
    : value(val),
      coefficient(coeff)
{
}

// operators
inline ValueCoefficientPair & operator+=(ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs)
{
    lhs.coefficient += rhs.coefficient;

    return lhs;
}

inline ValueCoefficientPair operator+(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs)
{
    return ValueCoefficientPair(lhs.value, lhs.coefficient + rhs.coefficient);
}

inline ValueCoefficientPair operator*(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs)
{
    return ValueCoefficientPair(lhs.value * rhs.value, lhs.coefficient * rhs.coefficient);
}

inline bool operator==(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs)
{
    return lhs.value == rhs.value && lhs.coefficient == rhs.coefficient;
}

inline bool operator!=(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs)
{
    return lhs.value != rhs.value && lhs.coefficient != rhs.coefficient;
}

inline bool operator<(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs)
{
    return lhs.value < rhs.value;
}

inline void swap(ValueCoefficientPair & lhs, ValueCoefficientPair & rhs)
{
    using std::swap;

    swap(lhs.value, rhs.value);
    swap(lhs.coefficient, rhs.coefficient);
}

} // internal namespace
} // ext namespace
} // gf2Algebra namespace

#endif // GF2ALGEBRA_EXT_INTERNAL_VALUECOEFFICIENTPAIR_HXX
