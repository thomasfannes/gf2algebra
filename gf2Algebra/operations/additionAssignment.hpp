/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_OPERATIONS_ADDITIONASSIGNMENT_HPP
#define GF2ALGEBRA_OPERATIONS_ADDITIONASSIGNMENT_HPP

#include "../representation.hpp"

namespace gf2Algebra {

void addAssign(
        SparseRepresentation & lhs,
        const SparseRepresentation & rhs);

template <typename RhsIndexMap>
void addAssign(
        SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs);

template <typename LhsIndexMap>
void addAssign(
        std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs);

template <typename LhsIndexMap, typename RhsIndexMap>
void addAssign(
        std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs);




} // namespace gf2Algebra

#include "additionAssignment.hxx"

#endif // GF2ALGEBRA_OPERATIONS_ADDITIONASSIGNMENT_HPP
