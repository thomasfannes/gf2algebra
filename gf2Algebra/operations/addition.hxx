/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_OPERATIONS_ADDITION_HXX
#define GF2ALGEBRA_OPERATIONS_ADDITION_HXX

#include "addition.hpp"
#include "../iterator.hpp"

namespace gf2Algebra {
namespace internal {

template <typename ordered_input_iterator_1, typename ordered_input_iterator_2, typename ordered_output_iterator>
void default_add(
        std::pair<ordered_input_iterator_1, ordered_input_iterator_1> lhs,
        std::pair<ordered_input_iterator_2,ordered_input_iterator_2> rhs,
        ordered_output_iterator out)
{
    // addition of both elements
    while(lhs.first != lhs.second && rhs.first != rhs.second)
    {
        if(lhs.first->value < rhs.first->value)
            *out++ = *lhs.first++;
        else if(rhs.first->value < lhs.first->value)
            *out++ = *rhs.first++;
        else
            *out++ = *lhs.first++ + *rhs.first++;
    }

    // addition of the remaining elements
    std::copy(lhs.first, lhs.second, out);
    std::copy(rhs.first, rhs.second, out);
}


} // internal namespace


inline void add(const SparseRepresentation & lhs, const SparseRepresentation & rhs, SparseRepresentation & tgt)
{
    internal::default_add(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}



template <typename TgtIndexMap>
void add(
        const SparseRepresentation & lhs,
        const SparseRepresentation & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{
    internal::default_add(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

template <typename RhsIndexMap>
void add(
        const SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        SparseRepresentation & tgt)
{
    internal::default_add(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

template <typename RhsIndexMap, typename TgtIndexMap>
void add(
        const SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{
    internal::default_add(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

template <typename LhsIndexMap>
void add(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs,
        SparseRepresentation & tgt)
{
    internal::default_add(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

template <typename LhsIndexMap, typename TgtIndexMap>
void add(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{
    internal::default_add(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

template <typename LhsIndexMap, typename RhsIndexMap>
void add(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        SparseRepresentation & tgt)
{
    internal::default_add(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

template <typename LhsIndexMap, typename RhsIndexMap, typename TgtIndexMap>
void add(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{
    internal::default_add(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

} // namespace gf2Algebra


#endif // GF2ALGEBRA_ADDITION_HXX
