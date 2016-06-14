/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/


#ifndef GF2ALGEBRA_OPERATIONS_HPP
#define GF2ALGEBRA_OPERATIONS_HPP

#include "sparseElement.hpp"
#include "denseElement.hpp"
#include "semiDenseElement.hpp"

namespace gf2Algebra {

SparseElement add(const SparseElement & s1, const SparseElement & s2);
SparseElement multiplySparse(const SparseElement & s1, const SparseElement & s2);

DenseElement add(const DenseElement & d1, const DenseElement & d2);
DenseElement multiplyDense(const DenseElement & d1, const DenseElement & d2);

SemiDenseElement add(const SemiDenseElement &s1, const SemiDenseElement &s2);
SemiDenseElement multiplySemiDense(const SemiDenseElement &s1, const SemiDenseElement &s2);


} // namespace gf2Algebra

#endif // GF2ALGEBRA_OPERATIONS_HPP
