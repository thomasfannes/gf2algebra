/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_INTERNAL_DENSEREPRESENTATIONITERATOR_HXX
#define GF2ALGEBRA_EXT_INTERNAL_DENSEREPRESENTATIONITERATOR_HXX

#include "denseRepresentationIterator.hpp"

namespace gf2Algebra {
namespace ext {
namespace internal {

#define TDEF template <typename IndexMap>
#define CDEF DenseElementToValueCoefficientTransformer<IndexMap>


TDEF
CDEF::DenseElementToValueCoefficientTransformer(const DenseRepresentation & x, const IndexMap & idxMap)
    : indexMap(idxMap),
      container(&x)
{
}

TDEF
CDEF::DenseElementToValueCoefficientTransformer()
    : container(0)
{
}

TDEF
const ValueCoefficientPair CDEF::operator()(std::size_t pos) const
{
    return ValueCoefficientPair(indexMap.fromIndex(pos), container->operator [](pos));
}


#undef CDEF
#define CDEF DenseRepresentationAdder<IndexMap>


TDEF
CDEF::DenseRepresentationAdder(DenseRepresentation & x, const IndexMap & map)
    : container(&x),
      indexMap(map)
{
}

TDEF
void CDEF::operator()(const ValueCoefficientPair & vcp) const
{
    container->operator [](indexMap.fromGroupValue(vcp.value)) += vcp.coefficient;
}

#undef TDEF
#undef CDEF

} // internal namespace
} // ext namespace
} // namespace gf2Algebra

#endif  // GF2ALGEBRA_EXT_INTERNAL_DENSEREPRESENTATIONITERATOR_HXX
