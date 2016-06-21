#ifndef GF2ALGEBRA_OPERATIONS_COPY_HPP
#define GF2ALGEBRA_OPERATIONS_COPY_HPP

#include "../representation.hpp"
#include "../identityIndexMap.hpp"

namespace gf2Algebra {

void copy(const SparseRepresentation & source, SparseRepresentation & target);

template <typename TgtIndexMap>
void copy(
        const SparseRepresentation & source,
        std::pair<DenseRepresentation, TgtIndexMap> & target);

template <typename SrcIndexMap>
void copy(
        const std::pair<DenseRepresentation, SrcIndexMap> & source,
        SparseRepresentation & target);

template <typename SrcIndexMap, typename TgtIndexMap>
void copy(
        const std::pair<DenseRepresentation, SrcIndexMap> & source,
        std::pair<DenseRepresentation, TgtIndexMap> & target);

template <>
void copy(
        const std::pair<DenseRepresentation, IdentityIndexMap> & source,
        std::pair<DenseRepresentation, IdentityIndexMap> & target
        );

}

#include "copy.hxx"

#endif // GF2ALGEBRA_OPERATIONS_COPY_HPP

