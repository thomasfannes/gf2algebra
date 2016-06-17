/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_OPERATIONS_TRANSFORM_HPP
#define GF2ALGEBRA_OPERATIONS_TRANSFORM_HPP

#include "../representation.hpp"

namespace gf2Algebra {

template <typename IndexMap>
void makeDense(const SparseRepresentation & element, DenseRepresentation & tgt, const IndexMap & tgtIndexMap);

template <typename IndexMap>
void makeSparse(const DenseRepresentation & element, SparseRepresentation & tgt, const IndexMap & elementIndexMap);


} // namespace gf2Algebra

#include "transform.hxx"

#endif // GF2ALGEBRA_OPERATIONS_TRANSFORM_HPP
