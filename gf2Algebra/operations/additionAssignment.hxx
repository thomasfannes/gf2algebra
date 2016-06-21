/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_OPERATIONS_ADDITIONASSIGNMENT_HXX
#define GF2ALGEBRA_OPERATIONS_ADDITIONASSIGNMENT_HXX

#include "additionAssignment.hpp"
#include "addition.hpp"

namespace gf2Algebra {
namespace internal {

template <typename rhs_iterator, typename out_iterator>
void add_to_dense(const std::pair<rhs_iterator, rhs_iterator> & rhs, out_iterator out)
{
    for(rhs_iterator it = rhs.first; it != rhs.second; ++it)
        (*out)++ = *it;
}

} // internal namespace


void addAssign(SparseRepresentation & lhs, const SparseRepresentation & rhs)
{
    SparseRepresentation res;
    res.reserve(lhs.size() + rhs.size());

    add(lhs, rhs, res);
    std::swap(lhs, res);
}



template <typename RhsIndexMap>
void addAssign(
        SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs)
{
    SparseRepresentation res;
    res.reserve(rhs.first.size());

    add(lhs, rhs, res);
    std::swap(lhs, res);
}

template <typename LhsIndexMap>
void addAssign(
        std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs)
{
    internal::add_to_dense(
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(lhs)
                );
}


template <typename LhsIndexMap, typename RhsIndexMap>
void addAssign(
        std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs)
{
    internal::add_to_dense(
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(lhs)
                );
}



} // namespace gf2Algebra


#endif // GF2ALGEBRA_OPERATIONS_ADDITIONASSIGNMENT_HXX
