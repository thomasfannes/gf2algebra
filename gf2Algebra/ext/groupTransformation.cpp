/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "groupTransformation.hpp"

namespace gf2Algebra {
namespace ext {


BitMapTransformer::BitMapTransformer(const Bitmap & srcToTgtMap)
{
    initializeData(srcToTgtMap);
}

internal::ValueCoefficientPair BitMapTransformer::operator()(const internal::ValueCoefficientPair & vcp) const
{
    Z2k::storage_type result = 0;
    Z2k::storage_type src = vcp.value.getValue();
    for(std::size_t i = 0; i < data_.size(); ++i)
    {
        const SrcToTgt & el = data_[i];
        if(src & el.srcMask)
            result |= el.tgtResult;
    }

    return internal::ValueCoefficientPair(Z2k(result), vcp.coefficient);
}

void BitMapTransformer::initializeData(const Bitmap & srcToTgtMap)
{
    for(Bitmap::const_iterator it = srcToTgtMap.begin(); it != srcToTgtMap.end(); ++it)
    {
        SrcToTgt el;
        el.srcMask = (1 << it->first);
        el.tgtResult = (1 << it->second);

        data_.push_back(el);
    }
}

} // ext namespace
} // gf2Algebra namespace

