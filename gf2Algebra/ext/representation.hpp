/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_REPRESENTATION_HPP
#define GF2ALGEBRA_EXT_REPRESENTATION_HPP

#include "../config.hpp"
#include "internal/valueCoefficientPair.hpp"
#include <vector>
#include <boost/type_traits/integral_constant.hpp>


namespace gf2Algebra {
namespace ext {



typedef std::pair<std::size_t, GaloisField> SparseElement;
typedef std::vector<GaloisField> DenseRepresentation;
typedef std::vector<SparseElement> SparseRepresentation;

inline bool compare_on_index(const SparseElement & lhs, const SparseElement & rhs)
{
    return lhs.first < rhs.first;
}


template <typename T>
struct is_representation : public boost::false_type {};

template <> struct is_representation<DenseRepresentation> : public boost::true_type {};
template <> struct is_representation<SparseRepresentation> : public boost::true_type {};

bool isZero(const SparseRepresentation & representation);
bool isZero(const DenseRepresentation & representation);

std::size_t countNonZero(const SparseRepresentation & representation);
std::size_t countNonZero(const DenseRepresentation & representation);

void initialize(SparseRepresentation & representation);
void initialize(DenseRepresentation & representation, unsigned char k);


void reset(DenseRepresentation & representation);
void reset(SparseRepresentation & representation);


} // ext namespace
} // gf2Algebra namespace

#include "representation.hxx"

#endif // GF2ALGEBRA_EXT_REPRESENTATION_HPP


