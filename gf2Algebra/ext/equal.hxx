/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_EQUAL_HXX
#define GF2ALGEBRA_EXT_EQUAL_HXX

#include "equal.hpp"
#include "iterator.hpp"

namespace gf2Algebra {
namespace ext {
namespace internal {

template <typename vcp_iterator>
vcp_iterator continueZero(vcp_iterator current, vcp_iterator last)
{
    while(current != last && current->coefficient == GaloisField::zero)
        ++current;

    return current;
}

template <typename vcp_iterator1, typename vcp_iterator2>
bool check_equal(
        const std::pair<vcp_iterator1, vcp_iterator1> & range1,
        const std::pair<vcp_iterator2, vcp_iterator2> & range2
        )
{
    vcp_iterator1 it1 = continueZero(range1.first, range1.second);
    vcp_iterator2 it2 = continueZero(range2.first, range2.second);

    while(it1 != range1.second && it2 != range2.second)
    {
        if(*it1 != *it2)
            return false;

        ++it1, ++it2;

        it1 = continueZero(it1, range1.second);
        it2 = continueZero(it2, range2.second);
    }

    return it1 == range1.second && it2 == range2.second;
}

} // internal namespace

template <typename Rep1, typename Rep2, typename IndexMap1, typename IndexMap2>
bool equal(
        const Rep1 & lhs,
        const Rep2 & rhs,
        const IndexMap1 & lhsIndexMap,
        const IndexMap2 & rhsIndexMap,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value >::type * /*dummy*/ = 0
        )
{
    return internal::check_equal(
                make_value_coefficient_input_range(lhs, lhsIndexMap),
                make_value_coefficient_input_range(rhs, rhsIndexMap)
                );
}

} // ext namespace
} // namespace gf2Algebra

#endif // GF2ALGEBRA_EXT_EQUAL_HXX
