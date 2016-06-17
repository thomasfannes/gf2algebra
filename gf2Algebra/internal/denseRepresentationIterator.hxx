/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_INTERNAL_DENSEREPRESENTATIONITERATOR_HXX
#define GF2ALGEBRA_INTERNAL_DENSEREPRESENTATIONITERATOR_HXX

#include "denseRepresentationIterator.hpp"

namespace gf2Algebra {
namespace internal {

#define TDEF template <typename Representation, typename IndexMap, typename Container>
#define CDEF DenseRepresentationListIteratorBase<Representation, IndexMap, Container>


TDEF
CDEF::DenseRepresentationListIteratorBase(IndexMap map)
    : container(0),
      pos(0),
      indexMap(map)
{

}

TDEF
CDEF::DenseRepresentationListIteratorBase(Container & x, IndexMap map)
    : container(&x),
      pos(0),
      indexMap(map)
{

}

TDEF
CDEF::DenseRepresentationListIteratorBase(Container & x, std::size_t curPos, IndexMap map)
    : container(&x),
      pos(curPos),
      indexMap(map)
{

}

TDEF
bool CDEF::equal(const CDEF & rhs) const
{
    return container == rhs.container && pos == rhs.pos;
}

TDEF
void CDEF::increment()
{
    ++pos;
}

TDEF
void CDEF::decrement()
{
    --pos;
}

TDEF
void CDEF::advance(int n)
{
    pos += n;
}

TDEF
Representation CDEF::operator*() const
{
    return Representation(indexMap.fromIndex(pos), container->operator[](pos));
}

TDEF
TemporaryPointerProxy<Representation> CDEF::operator->() const
{
    return TemporaryPointerProxy<Representation>(operator *());
}

#undef TDEF
#undef CDEF



#define TDEF template <typename IndexMap>
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
} // namespace gf2Algebra

#endif  // GF2ALGEBRA_INTERNAL_DENSEREPRESENTATIONITERATOR_HXX
