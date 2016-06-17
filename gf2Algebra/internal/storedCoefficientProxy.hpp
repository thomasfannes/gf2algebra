/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_INTERNAL_STOREDCOEFFICIENTPROXY_HPP
#define GF2ALGEBRA_INTERNAL_STOREDCOEFFICIENTPROXY_HPP

#include "../valueCoefficientPair.hpp"
#include "../config.hpp"

namespace gf2Algebra {
namespace internal {

class StoredCoefficientProxy
{   
public:
    typedef GaloisField             field_type;
    typedef Z2k                     group_type;

    StoredCoefficientProxy(const group_type & val, field_type & coeff);
    operator ValueCoefficientPair() const;

    const group_type value;
    field_type & coefficient;
};


bool operator==(const StoredCoefficientProxy & lhs, const StoredCoefficientProxy & rhs);
bool operator!=(const StoredCoefficientProxy & lhs, const StoredCoefficientProxy & rhs);
bool operator<(const StoredCoefficientProxy & lhs, const StoredCoefficientProxy & rhs);
StoredCoefficientProxy & operator+=(StoredCoefficientProxy & lhs, const ValueCoefficientPair & rhs);
ValueCoefficientPair operator+(const StoredCoefficientProxy & lhs, const StoredCoefficientProxy & rhs);
ValueCoefficientPair operator*(const StoredCoefficientProxy & lhs, const StoredCoefficientProxy & rhs);

} // namespace internal
} // namespace gf2Algebra

#endif // GF2ALGEBRA_INTERNAL_STOREDCOEFFICIENTPROXY_HPP
