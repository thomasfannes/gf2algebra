/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_OPERATIONS_MULTIPLICATION_HPP
#define GF2ALGEBRA_OPERATIONS_MULTIPLICATION_HPP

namespace gf2Algebra {

#include "../representation.hpp"

void multiply(
        const SparseRepresentation & lhs,
        const SparseRepresentation & rhs,
        SparseRepresentation & tgt);

template <typename TgtIndexMap>
void multiply(
        const SparseRepresentation & lhs,
        const SparseRepresentation & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt);

template <typename RhsIndexMap>
void multiply(
        const SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        SparseRepresentation & tgt);

template <typename RhsIndexMap, typename TgtIndexMap>
void multiply(
        const SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt);

template <typename LhsIndexMap>
void multiply(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs,
        SparseRepresentation & tgt);

template <typename LhsIndexMap, typename TgtIndexMap>
void multiply(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt);

template <typename LhsIndexMap, typename RhsIndexMap>
void multiply(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        SparseRepresentation & tgt);

template <typename LhsIndexMap, typename RhsIndexMap, typename TgtIndexMap>
void multiply(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt);

void multiply_FFT(
        unsigned char noBits,
        const SparseRepresentation & lhs,
        const SparseRepresentation & rhs,
        SparseRepresentation & tgt);

template <typename TgtIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const SparseRepresentation & lhs,
        const SparseRepresentation & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt);

template <typename RhsIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        SparseRepresentation & tgt);

template <typename RhsIndexMap, typename TgtIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt);

template <typename LhsIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs,
        SparseRepresentation & tgt);

template <typename LhsIndexMap, typename TgtIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt);

template <typename LhsIndexMap, typename RhsIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        SparseRepresentation & tgt);

template <typename LhsIndexMap, typename RhsIndexMap, typename TgtIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt);



} // namespace gf2Algebra

#include "multiplication.hxx"

#endif // GF2ALGEBRA_OPERATIONS_MULTIPLICATION_HPP
