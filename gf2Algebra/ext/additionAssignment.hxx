/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_ADDITIONASSIGNMENT_HXX
#define GF2ALGEBRA_EXT_ADDITIONASSIGNMENT_HXX

#include "additionAssignment.hpp"
#include "iterator.hpp"

namespace gf2Algebra {
namespace ext {

template <typename Rep1, typename Rep2, typename IndexMap1, typename IndexMap2>
void addAssign(
        Rep1 & lhs,
        const Rep2 & rhs,
        const IndexMap1 & lhsIndexMap,
        const IndexMap2 & rhsIndexMap,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value >::type * /*dummy*/
        )
{
    typedef typename representation_iterator_traits<Rep2, IndexMap2>::value_coefficient_input_iterator vcit;
    typedef typename representation_iterator_traits<Rep1, IndexMap1>::unordered_value_coefficient_output_iterator out_it;

    out_it out = make_unordered_value_coefficient_output_iterator(lhs, lhsIndexMap);

    for(std::pair<vcit, vcit> p = make_value_coefficient_input_range(rhs, rhsIndexMap); p.first != p.second; ++p.first)
        *out++ = *p.first;
}

} // ext namespace
} // namespace gf2Algebra


#endif // GF2ALGEBRA_EXT_ADDITIONASSIGNMENT_HXX

