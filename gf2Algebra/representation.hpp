/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_REPRESENTATION_HPP
#define GF2ALGEBRA_REPRESENTATION_HPP

#include "config.hpp"
#include "valueCoefficientPair.hpp"
#include <vector>


namespace gf2Algebra {

typedef std::vector<GaloisField> DenseRepresentation;
typedef std::vector<ValueCoefficientPair> SparseRepresentation;

bool isZero(const SparseRepresentation & representation);
bool isZero(const DenseRepresentation & representation);

std::size_t countNonZero(const SparseRepresentation & representation);
std::size_t countNonZero(const DenseRepresentation & representation);

void initialize(DenseRepresentation & representation, std::size_t k);
void initialize(SparseRepresentation & representation, std::size_t k);

void reset(DenseRepresentation & representation);
void reset(SparseRepresentation & representation);

} // gf2Algebra namespace

#endif // GF2ALGEBRA_REPRESENTATION_HPP
