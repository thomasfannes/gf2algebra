/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "valueCoefficientPair.hpp"
#include <cassert>

namespace gf2Algebra {

ValueCoefficientPair::ValueCoefficientPair()
    : value(group_type()),
      coefficient(field_type::zero)
{
}

ValueCoefficientPair::ValueCoefficientPair(group_type val, field_type coeff)
    : value(val),
      coefficient(coeff)
{
}

// operators
ValueCoefficientPair & operator+=(ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs)
{
    lhs.coefficient += rhs.coefficient;

    return lhs;
}

ValueCoefficientPair operator+(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs)
{
    return ValueCoefficientPair(lhs.value, lhs.coefficient + rhs.coefficient);
}

ValueCoefficientPair operator*(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs)
{
    return ValueCoefficientPair(lhs.value * rhs.value, lhs.coefficient * rhs.coefficient);
}

bool operator==(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs)
{
    return lhs.value == rhs.value && lhs.coefficient == rhs.coefficient;
}

bool operator!=(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs)
{
    return lhs.value != rhs.value && lhs.coefficient != rhs.coefficient;
}

bool operator<(const ValueCoefficientPair & lhs, const ValueCoefficientPair & rhs)
{
    return lhs.value < rhs.value;
}

void swap(ValueCoefficientPair & lhs, ValueCoefficientPair & rhs)
{
    using std::swap;

    swap(lhs.value, rhs.value);
    swap(lhs.coefficient, rhs.coefficient);
}

} // gf2Algebra namespace
