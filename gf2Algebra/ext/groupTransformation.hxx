/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "groupTransformation.hpp"
#include "iterator.hpp"

namespace gf2Algebra {
namespace ext {

template <typename TransformFunctor, typename Rep1, typename Rep2, typename IndexMap1, typename IndexMap2>
void change_dimensionality(
        const Rep1 & src,
        Rep2 & tgt,
        const IndexMap1 & srcIndexMap,
        const IndexMap2 & tgtIndexMap,
        const TransformFunctor & f,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value>::type * /*dummy*/
        )
{
    typedef typename representation_iterator_traits<Rep1, IndexMap1>::value_coefficient_input_iterator vcit;
    typedef typename representation_iterator_traits<Rep2, IndexMap2>::unordered_value_coefficient_output_iterator outit;

    outit out = make_unordered_value_coefficient_output_iterator(tgt, tgtIndexMap);

    for(std::pair<vcit,vcit> p = make_value_coefficient_input_range(src, srcIndexMap); p.first != p.second; ++p.first)
        *out++ = f(*p.first++);
}

template <typename Rep1, typename Rep2, typename IndexMap1, typename IndexMap2>
void aggregate_bits(
        const Rep1 & src,
        Rep2 & tgt,
        const IndexMap1 & srcIndexMap,
        const IndexMap2 & tgtIndexMap,
        Z2k::storage_type mask,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value>::type * /*dummy*/
        )
{
    typedef typename representation_iterator_traits<Rep1, IndexMap1>::value_coefficient_input_iterator vcit;
    typedef typename representation_iterator_traits<Rep2, IndexMap2>::masked_unordered_value_coefficient_output_iterator outit;

    outit out = make_unordered_value_coefficient_output_iterator(tgt, tgtIndexMap, mask);

    for(std::pair<vcit,vcit> p = make_value_coefficient_input_range(src, srcIndexMap); p.first != p.second; ++p.first)
        *out++ = *p.first++;
}

} // namespace ext
} // namespace gf2Algebra
