/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_ADDITION_HXX
#define GF2ALGEBRA_EXT_ADDITION_HXX

#include "addition.hpp"
#include "iterator.hpp"

namespace gf2Algebra {
namespace ext {

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

template <typename Rep1, typename Rep2, typename Rep3, typename IndexMap1, typename IndexMap2, typename IndexMap3>
void add(
        const Rep1 & lhs,
        const Rep2 & rhs,
        Rep3 & tgt,
        const IndexMap1 & lhsIndexMap,
        const IndexMap2 & rhsIndexMap,
        const IndexMap3 & tgtIndexMap,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value && is_representation<Rep3>::value >::type * /*dummy*/
        )
{
    internal::default_add(
                make_value_coefficient_input_range(lhs, lhsIndexMap),
                make_value_coefficient_input_range(rhs, rhsIndexMap),
                make_ordered_value_coefficient_output_iterator(tgt, tgtIndexMap)
                );
}



} // ext namespace
} // namespace gf2Algebra


#endif // GF2ALGEBRA_EXT_ADDITION_HXX
