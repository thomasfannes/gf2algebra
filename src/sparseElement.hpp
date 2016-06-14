/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_SPARSEELEMENT_HPP
#define GF2ALGEBRA_SPARSEELEMENT_HPP


#include <vector>
#include "gf256.hpp"
#include "z2k.hpp"



namespace gf2Algebra {
namespace config {

struct SparseCoefficient
{
    typedef GF256               field_type;
    typedef Z2k                 group_type;

    SparseCoefficient();
    SparseCoefficient(const field_type & coeff, const group_type & val);

    SparseCoefficient & operator+=(const SparseCoefficient & rhs);
    SparseCoefficient operator+(const SparseCoefficient & rhs) const;
    SparseCoefficient operator*(const SparseCoefficient & rhs) const;
    bool operator<(const SparseCoefficient & rhs) const;
    bool operator==(const SparseCoefficient & rhs) const;
    bool operator!=(const SparseCoefficient & rhs) const;

    bool isZero() const;

    field_type coefficient;
    group_type value;
};

void swap(const SparseCoefficient & lhs, const SparseCoefficient & rhs);

} // config namespace

/*
 * Group algebra GF(2^8)[Z_2^k]
 */
class SparseElement : public std::vector<config::SparseCoefficient>
{
public:
    typedef config::SparseCoefficient                   sparse_coefficient;
    typedef std::vector<config::SparseCoefficient>      base;
    typedef sparse_coefficient::field_type              field_type;
    typedef sparse_coefficient::group_type              group_type;

    SparseElement();

    bool isZero() const;
    bool isValid() const;
    std::size_t countNonZero();
};

} // gf2Algebra namespace

#endif // GF2ALGEBRA_SPARSEELEMENT_HPP
