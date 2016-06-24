/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_INTERNAL_SPARSEREPRESENTATIONITERATOR_HPP
#define GF2ALGEBRA_EXT_INTERNAL_SPARSEREPRESENTATIONITERATOR_HPP

#include "../representation.hpp"
#include <cassert>
#include <boost/iterator/transform_iterator.hpp>

namespace gf2Algebra {
namespace ext {
namespace internal {

template <typename IndexMap>
struct SparseElementToValueCoefficientTransformer
{
    typedef const ValueCoefficientPair result_type;

    explicit SparseElementToValueCoefficientTransformer(const IndexMap & idxMap = IndexMap());
    result_type operator()(const SparseElement & element) const;

    IndexMap indexMap;
};

template <typename IndexMap>
class SparseElementValueCoefficientIterator
        : public boost::transform_iterator<SparseElementToValueCoefficientTransformer<IndexMap>, SparseRepresentation::const_iterator>
{
public:
    explicit SparseElementValueCoefficientIterator(
            SparseRepresentation::const_iterator iterator = SparseRepresentation::const_iterator(),
            const IndexMap & idxMap = IndexMap()
            )
        : boost::transform_iterator<SparseElementToValueCoefficientTransformer<IndexMap>, SparseRepresentation::const_iterator>(iterator, SparseElementToValueCoefficientTransformer<IndexMap>(idxMap))
    {
    }
};

template <typename IndexMap>
struct SparseRepresentationOrderedAdder
{
    SparseRepresentationOrderedAdder(SparseRepresentation & x, const IndexMap & idxMap);
    void operator()(const ValueCoefficientPair & vcp) const;

protected:
    SparseRepresentation * container;
    IndexMap indexMap;
};


template <typename IndexMap>
struct SparseRepresentationUnorderedAdder
{
    SparseRepresentationUnorderedAdder(SparseRepresentation & x, const IndexMap & idxMap);
    ~SparseRepresentationUnorderedAdder();

    void operator()(const ValueCoefficientPair & vcp) const;
    void flush();

protected:
    SparseRepresentation * container;
    mutable SparseRepresentation temporary;
    mutable bool finished;
    IndexMap indexMap;
};



} // namespace internal
} // ext namespace
} // namespace gf2Algebra

#include "sparseRepresentationIterator.hxx"

#endif // GF2ALGEBRA_EXT_INTERNAL_SPARSEREPRESENTATIONITERATOR_HPP
