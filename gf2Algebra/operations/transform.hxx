/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_OPERATIONS_TRANSFORM_HXX
#define GF2ALGEBRA_OPERATIONS_TRANSFORM_HXX

#include "transform.hpp"
#include "../iterator.hpp"

namespace gf2Algebra {
namespace internal {

template <typename input_iterator, typename output_iterator>
void copy_element(std::pair<input_iterator, input_iterator> element, output_iterator out)
{
    std::copy(element.first, element.second, out);
}

} // internal namespace

template <typename IndexMap>
void makeDense(const SparseRepresentation & element, std::pair<DenseRepresentation, IndexMap> & tgt)
{
    makeDense(element, tgt.first, tgt.second);
}

template <typename IndexMap>
void makeDense(const SparseRepresentation & element, DenseRepresentation & tgt, const IndexMap & tgtIndexMap)
{
    internal::copy_element(
                make_value_coefficient_input_range(element),
                make_ordered_value_coefficient_output_iterator(tgt, tgtIndexMap)
                );
}

template <typename IndexMap>
void makeSparse(const std::pair<DenseRepresentation, IndexMap> & element, SparseRepresentation & tgt)
{
    makeSparse(element.first, tgt, element.second);
}

template <typename IndexMap>
void makeSparse(const DenseRepresentation & element, SparseRepresentation & tgt, const IndexMap & elementIndexMap)
{
    internal::copy_element(
                make_value_coefficient_input_range(element, elementIndexMap),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

} // namespace gf2Algebra

#endif // GF2ALGEBRA_OPERATIONS_TRANSFORM_HXX
