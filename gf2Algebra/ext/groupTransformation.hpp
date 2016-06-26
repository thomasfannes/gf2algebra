/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_GROUPTRANSFORMATION_HPP
#define GF2ALGEBRA_EXT_GROUPTRANSFORMATION_HPP

#include "representation.hpp"
#include <map>
#include <vector>
#include <boost/utility/enable_if.hpp>

namespace gf2Algebra {
namespace ext {

struct BitMapTransformer
{
    BitMapTransformer(const Bitmap & srcToTgtMap = Bitmap());

    internal::ValueCoefficientPair operator()(const internal::ValueCoefficientPair & src) const;

private:
    struct SrcToTgt
    {
        Z2k::storage_type srcMask;
        Z2k::storage_type tgtResult;
    };

    void initializeData(const Bitmap & srcToTgtMap);
    std::vector<SrcToTgt> data_;
};

template <typename TransformFunctor, typename Rep1, typename Rep2, typename IndexMap1, typename IndexMap2>
void change_dimensionality(
        const Rep1 & src,
        Rep2 & tgt,
        const IndexMap1 & srcIndexMap,
        const IndexMap2 & tgtIndexMap,
        const TransformFunctor & f = TransformFunctor(),
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value>::type * /*dummy*/ = 0
        );

template <typename Rep1, typename Rep2, typename IndexMap1, typename IndexMap2>
void aggregate_bits(
        const Rep1 & src,
        Rep2 & tgt,
        const IndexMap1 & srcIndexMap,
        const IndexMap2 & tgtIndexMap,
        Z2k::storage_type mask,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value>::type * /*dummy*/ = 0
        );

} // namespace ext
} // namespace gf2Algebra

#include "groupTransformation.hxx"

#endif // GF2ALGEBRA_EXT_GROUPTRANSFORMATION_HPP
