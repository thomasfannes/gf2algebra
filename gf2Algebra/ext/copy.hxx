#ifndef GF2ALGEBRA_EXT_COPY_HXX
#define GF2ALGEBRA_EXT_COPY_HXX

#include "copy.hpp"
#include "iterator.hpp"

namespace gf2Algebra {
namespace ext {

template <typename Rep1, typename Rep2, typename IndexMap1, typename IndexMap2>
void copy(
        const Rep1 & source,
        Rep2 & target,
        const IndexMap1 & sourceIndexMap,
        const IndexMap2 & targetIndexMap,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value  >::type * /*dummy*/ = 0
        )
{
    typedef typename representation_iterator_traits<Rep1, IndexMap1>::value_coefficient_input_iterator it1;

    std::pair<it1, it1> p = make_value_coefficient_input_range(source, sourceIndexMap);
    std::copy(
                p.first,
                p.second,
                make_ordered_value_coefficient_output_iterator(target, targetIndexMap)
                );
}


} // ext namespace
} // gf2Algebra namespace

#endif // GF2ALGEBRA_EXT_COPY_HXX

