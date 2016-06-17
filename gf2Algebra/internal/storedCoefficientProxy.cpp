/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "storedCoefficientProxy.hpp"
#include <cassert>
#include <iostream>

namespace gf2Algebra {
namespace internal {

StoredCoefficientProxy::StoredCoefficientProxy(const group_type & val, field_type & coeff)
    : value(val),
      coefficient(coeff)
{
}

bool operator==(const StoredCoefficientProxy & lhs, const StoredCoefficientProxy & rhs)
{
    return static_cast<ValueCoefficientPair>(lhs) == static_cast<ValueCoefficientPair>(rhs);
}

bool operator!=(const StoredCoefficientProxy & lhs, const StoredCoefficientProxy & rhs)
{
    return static_cast<ValueCoefficientPair>(lhs) != static_cast<ValueCoefficientPair>(rhs);
}

bool operator<(const StoredCoefficientProxy & lhs, const StoredCoefficientProxy & rhs)
{
    return static_cast<ValueCoefficientPair>(lhs) < static_cast<ValueCoefficientPair>(rhs);
}

StoredCoefficientProxy::operator ValueCoefficientPair() const
{
    return ValueCoefficientPair(value, coefficient);
}


StoredCoefficientProxy & operator+=(StoredCoefficientProxy & lhs, const ValueCoefficientPair & rhs)
{
    lhs.coefficient += rhs.coefficient;

    return lhs;
}

ValueCoefficientPair operator+(const StoredCoefficientProxy & lhs, const StoredCoefficientProxy & rhs)
{
    return static_cast<ValueCoefficientPair>(lhs) + static_cast<ValueCoefficientPair>(rhs);
}

ValueCoefficientPair operator*(const StoredCoefficientProxy & lhs, const StoredCoefficientProxy & rhs)
{
    return static_cast<ValueCoefficientPair>(lhs) + static_cast<ValueCoefficientPair>(rhs);
}

} // namespace internal
} // namespace gf2Algebra
