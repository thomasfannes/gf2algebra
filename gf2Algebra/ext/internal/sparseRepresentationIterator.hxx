/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_INTERNAL_SPARSEREPRESENTATIONITERATOR_HXX
#define GF2ALGEBRA_EXT_INTERNAL_SPARSEREPRESENTATIONITERATOR_HXX

#include "sparseRepresentationIterator.hpp"
#include <algorithm>

namespace gf2Algebra {
namespace ext {
namespace internal {

#define TDEF template <typename IndexMap>
#define CDEF SparseElementToValueCoefficientTransformer<IndexMap>

TDEF
CDEF::SparseElementToValueCoefficientTransformer(const IndexMap & idxMap)
    : indexMap(idxMap)
{
}

TDEF
typename CDEF::result_type CDEF::operator()(const SparseElement & element) const
{
    return ValueCoefficientPair(indexMap.fromIndex(element.first), element.second);
}


#undef CDEF
#define CDEF SparseRepresentationOrderedAdder<IndexMap>

TDEF
CDEF::SparseRepresentationOrderedAdder(SparseRepresentation & x, const IndexMap & idxMap)
    : container(&x)
    , indexMap(idxMap)
{
}

TDEF
void CDEF::operator()(const ValueCoefficientPair & vcp) const
{
    if(vcp.coefficient != GaloisField::zero)
    {
        std::size_t idx = indexMap.fromGroupValue(vcp.value);
        assert(container->empty() || container->back().first <= idx);

        if(container->empty() || container->back().first < idx)
            container->push_back(SparseElement(idx, vcp.coefficient));
        else
            container->back().second += vcp.coefficient;
    }
}

#undef CDEF
#define CDEF SparseRepresentationUnorderedAdder<IndexMap>

TDEF
CDEF::SparseRepresentationUnorderedAdder(SparseRepresentation & x, const IndexMap & idxMap)
    : container(&x),
      finished(true),
      indexMap(idxMap)
{
}

TDEF
CDEF::~SparseRepresentationUnorderedAdder()
{
    if(!finished)
        flush();
}

TDEF
void CDEF::operator()(const ValueCoefficientPair & vcp) const
{
    if(vcp.coefficient != GaloisField::zero)
    {
        temporary.push_back(SparseElement(indexMap.fromGroupValue(vcp.value), vcp.coefficient));
        finished = false;
    }
}

TDEF
void CDEF::flush()
{
    // add to the array and sort again
    container->insert(container->end(), temporary.begin(), temporary.end());
    std::sort(container->begin(), container->end(), compare_on_index);

    SparseRepresentation::const_iterator readIt = container->begin();
    SparseRepresentation::iterator writeIt = container->begin();

    while(readIt != container->end())
    {
        // set the current
        SparseElement cur = *readIt++;

        // continue over all similar elements
        while(readIt != container->end() && readIt->first == cur.first)
            cur.second += readIt++->second;

        // and if nonzero, add it
        if(cur.second != GaloisField::zero)
            *writeIt++ = cur;
    }

    // and cleanup
    container->erase(writeIt, container->end());
    temporary.clear();
    finished = true;
}

#undef TDEF
#undef CDEF


} // internal namespace
} // ext namespace
} // gf2Algebra namespace

#endif // GF2ALGEBRA_EXT_INTERNAL_SPARSEREPRESENTATIONITERATOR_HXX
