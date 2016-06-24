/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_ADDITION_HPP
#define GF2ALGEBRA_EXT_ADDITION_HPP

#include <boost/utility/enable_if.hpp>
#include "representation.hpp"

namespace gf2Algebra {
namespace ext {

template <typename Rep1, typename Rep2, typename Rep3, typename IndexMap1, typename IndexMap2, typename IndexMap3>
void add(
        const Rep1 & lhs,
        const Rep2 & rhs,
        Rep3 & tgt,
        const IndexMap1 & lhsIndexMap,
        const IndexMap2 & rhsIndexMap,
        const IndexMap3 & tgtIndexMap,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value && is_representation<Rep3>::value >::type * /*dummy*/ = 0
        );

} // ext namespace
} // namespace gf2Algebra

#include "addition.hxx"

#endif // GF2ALGEBRA_EXT_ADDITION_HPP
