/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_OPERATIONS_ADDITION_HPP
#define GF2ALGEBRA_OPERATIONS_ADDITION_HPP

#include "../representation.hpp"

namespace gf2Algebra {

void add(
        const SparseRepresentation & lhs,
        const SparseRepresentation & rhs,
        SparseRepresentation & tgt);

template <typename TgtIndexMap>
void add(
        const SparseRepresentation & lhs,
        const SparseRepresentation & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt);

template <typename RhsIndexMap>
void add(
        const SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        SparseRepresentation & tgt);

template <typename RhsIndexMap, typename TgtIndexMap>
void add(
        const SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt);

template <typename LhsIndexMap>
void add(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs,
        SparseRepresentation & tgt);

template <typename LhsIndexMap, typename TgtIndexMap>
void add(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt);

template <typename LhsIndexMap, typename RhsIndexMap>
void add(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        SparseRepresentation & tg);

template <typename LhsIndexMap, typename RhsIndexMap, typename TgtIndexMap>
void add(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt);

} // namespace gf2Algebra

#include "addition.hxx"

#endif // GF2ALGEBRA_OPERATIONS_ADDITION_HPP
