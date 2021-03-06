/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_COPY_HPP
#define GF2ALGEBRA_EXT_COPY_HPP

#include <boost/utility/enable_if.hpp>
#include "representation.hpp"

namespace gf2Algebra {
namespace ext {

template <typename Rep1, typename Rep2, typename IndexMap1, typename IndexMap2>
void copy(
        Rep1 & lhs,
        const Rep2 & rhs,
        const IndexMap1 & lhsIndexMap,
        const IndexMap2 & rhsIndexMap,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value  >::type * /*dummy*/ = 0
        );

} // ext namespace
} // gf2Algebra namespace

#include "copy.hxx"

#endif // GF2ALGEBRA_EXT_COPY_HPP

