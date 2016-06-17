/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_OPERATIONS_MULTIPLY_HPP
#define GF2ALGEBRA_OPERATIONS_MULTIPLY_HPP

namespace gf2Algebra {

#include "../representation.hpp"

void multiply(const SparseRepresentation & lhs, const SparseRepresentation & rhs, SparseRepresentation & tgt);

template <typename TgtIndexMap>
void multiply(const SparseRepresentation & lhs, const SparseRepresentation & rhs, DenseRepresentation & tgt, const TgtIndexMap & tgtIndexMap);

template <typename RhsIndexMap>
void multiply(const SparseRepresentation & lhs, const DenseRepresentation & rhs, SparseRepresentation & tgt, const RhsIndexMap & rhsIndexMap);

template <typename RhsIndexMap, typename TgtIndexMap>
void multiply(const SparseRepresentation & lhs, const DenseRepresentation & rhs, DenseRepresentation & tgt, const RhsIndexMap & rhsIndexMap, const TgtIndexMap & tgtIndexMap);

template <typename LhsIndexMap>
void multiply(const DenseRepresentation & lhs, const SparseRepresentation & rhs, SparseRepresentation & tgt, const LhsIndexMap & lhsIndexMap);

template <typename LhsIndexMap, typename TgtIndexMap>
void multiply(const DenseRepresentation & lhs, const SparseRepresentation & rhs, DenseRepresentation & tgt, const LhsIndexMap & lhsIndexMap, const TgtIndexMap & tgtIndexMap);

template <typename LhsIndexMap, typename RhsIndexMap>
void multiply(const DenseRepresentation & lhs, const DenseRepresentation & rhs, SparseRepresentation & tgt, const LhsIndexMap & lhsIndexMap, const RhsIndexMap & rhsIndexMap);

template <typename LhsIndexMap, typename RhsIndexMap, typename TgtIndexMap>
void multiply(const DenseRepresentation & lhs, const DenseRepresentation & rhs, DenseRepresentation & tgt, const LhsIndexMap & lhsIndexMap, const RhsIndexMap & rhsIndexMap, const TgtIndexMap & tgtIndexMap);


void multiply_FFT(unsigned char noBits, const SparseRepresentation & lhs, const SparseRepresentation & rhs, SparseRepresentation & tgt);

template <typename TgtIndexMap>
void multiply_FFT(unsigned char noBits, const SparseRepresentation & lhs, const SparseRepresentation & rhs, DenseRepresentation & tgt, const TgtIndexMap & tgtIndexMap);

template <typename RhsIndexMap>
void multiply_FFT(unsigned char noBits, const SparseRepresentation & lhs, const DenseRepresentation & rhs, SparseRepresentation & tgt, const RhsIndexMap & rhsIndexMap);

template <typename RhsIndexMap, typename TgtIndexMap>
void multiply_FFT(unsigned char noBits, const SparseRepresentation & lhs, const DenseRepresentation & rhs, DenseRepresentation & tgt, const RhsIndexMap & rhsIndexMap, const TgtIndexMap & tgtIndexMap);

template <typename LhsIndexMap>
void multiply_FFT(unsigned char noBits, const DenseRepresentation & lhs, const SparseRepresentation & rhs, SparseRepresentation & tgt, const LhsIndexMap & lhsIndexMap);

template <typename LhsIndexMap, typename TgtIndexMap>
void multiply_FFT(unsigned char noBits, const DenseRepresentation & lhs, const SparseRepresentation & rhs, DenseRepresentation & tgt, const LhsIndexMap & lhsIndexMap, const TgtIndexMap & tgtIndexMap);

template <typename LhsIndexMap, typename RhsIndexMap>
void multiply_FFT(unsigned char noBits, const DenseRepresentation & lhs, const DenseRepresentation & rhs, SparseRepresentation & tgt, const LhsIndexMap & lhsIndexMap, const RhsIndexMap & rhsIndexMap);

template <typename LhsIndexMap, typename RhsIndexMap, typename TgtIndexMap>
void multiply_FFT(unsigned char noBits, const DenseRepresentation & lhs, const DenseRepresentation & rhs, DenseRepresentation & tgt, const LhsIndexMap & lhsIndexMap, const RhsIndexMap & rhsIndexMap, const TgtIndexMap & tgtIndexMap);



template <typename TgtIndexMap>
void multiply(const SparseRepresentation & lhs, const SparseRepresentation & rhs, std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{ multiply(lhs, rhs, tgt.first, tgt.second); }

template <typename RhsIndexMap>
void multiply(const SparseRepresentation & lhs, const std::pair<DenseRepresentation, RhsIndexMap> & rhs, SparseRepresentation & tgt)
{ multiply(lhs, rhs.first, tgt, rhs.second); }

template <typename RhsIndexMap, typename TgtIndexMap>
void multiply(const SparseRepresentation & lhs, const std::pair<DenseRepresentation, RhsIndexMap> & rhs, std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{ multiply(lhs, rhs.first, tgt.first, rhs.second, tgt.second); }

template <typename LhsIndexMap>
void multiply(const std::pair<DenseRepresentation, LhsIndexMap> & lhs, const SparseRepresentation & rhs, SparseRepresentation & tgt)
{ multiply(lhs.first, rhs, tgt, lhs.second); }

template <typename LhsIndexMap, typename TgtIndexMap>
void multiply(const std::pair<DenseRepresentation, LhsIndexMap> & lhs, const SparseRepresentation & rhs, std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{ multiply(lhs.first, rhs, tgt.first, lhs.second, tgt.second); }

template <typename LhsIndexMap, typename RhsIndexMap>
void multiply(const std::pair<DenseRepresentation, LhsIndexMap> & lhs, const std::pair<DenseRepresentation, RhsIndexMap> & rhs, SparseRepresentation & tgt)
{ multiply(lhs.first, rhs.first, tgt, lhs.second, rhs.second); }

template <typename LhsIndexMap, typename RhsIndexMap, typename TgtIndexMap>
void multiply(const std::pair<DenseRepresentation, LhsIndexMap> & lhs, const std::pair<DenseRepresentation, RhsIndexMap> & rhs, std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{ multiply(lhs.first, rhs.first, tgt.first, lhs.second, rhs.second, tgt.second); }



template <typename TgtIndexMap>
void multiply_FFT(unsigned char noBits, const SparseRepresentation & lhs, const SparseRepresentation & rhs, std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{ multiply_FFT(noBits, lhs, rhs, tgt.first, tgt.second); }

template <typename RhsIndexMap>
void multiply_FFT(unsigned char noBits, const SparseRepresentation & lhs, const std::pair<DenseRepresentation, RhsIndexMap> & rhs, SparseRepresentation & tgt)
{ multiply_FFT(noBits, lhs, rhs.first, tgt, rhs.second); }

template <typename RhsIndexMap, typename TgtIndexMap>
void multiply_FFT(unsigned char noBits, const SparseRepresentation & lhs, const std::pair<DenseRepresentation, RhsIndexMap> & rhs, std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{ multiply_FFT(noBits, lhs, rhs.first, tgt.first, rhs.second, tgt.second); }

template <typename LhsIndexMap>
void multiply_FFT(unsigned char noBits, const std::pair<DenseRepresentation, LhsIndexMap> & lhs, const SparseRepresentation & rhs, SparseRepresentation & tgt)
{ multiply_FFT(noBits, lhs.first, rhs, tgt, lhs.second); }

template <typename LhsIndexMap, typename TgtIndexMap>
void multiply_FFT(unsigned char noBits, const std::pair<DenseRepresentation, LhsIndexMap> & lhs, const SparseRepresentation & rhs, std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{ multiply_FFT(noBits, lhs.first, rhs, tgt.first, lhs.second, tgt.second); }

template <typename LhsIndexMap, typename RhsIndexMap>
void multiply_FFT(unsigned char noBits, const std::pair<DenseRepresentation, LhsIndexMap> & lhs, const std::pair<DenseRepresentation, RhsIndexMap> & rhs, SparseRepresentation & tgt)
{ multiply_FFT(noBits, lhs.first, rhs.first, tgt, lhs.second, rhs.second); }

template <typename LhsIndexMap, typename RhsIndexMap, typename TgtIndexMap>
void multiply_FFT(unsigned char noBits, const std::pair<DenseRepresentation, LhsIndexMap> & lhs, const std::pair<DenseRepresentation, RhsIndexMap> & rhs, std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{ multiply_FFT(noBits, lhs.first, rhs.first, tgt.first, lhs.second, rhs.second, tgt.second); }



} // namespace gf2Algebra

#include "multiply.hxx"

#endif // GF2ALGEBRA_OPERATIONS_MULTIPLY_HPP
