/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_INTERNAL_DENSEREPRESENTATIONITERATOR_HPP
#define GF2ALGEBRA_EXT_INTERNAL_DENSEREPRESENTATIONITERATOR_HPP

#include "temporaryPointerProxy.hpp"
#include "../representation.hpp"
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/counting_iterator.hpp>

namespace gf2Algebra {
namespace ext {
namespace internal {

template <typename IndexMap>
struct DenseElementToValueCoefficientTransformer
{
    typedef const ValueCoefficientPair result_type;

    explicit DenseElementToValueCoefficientTransformer(const DenseRepresentation & x, const IndexMap & idxMap);
    DenseElementToValueCoefficientTransformer();

    const ValueCoefficientPair operator()(std::size_t pos) const;

    IndexMap indexMap;
    const DenseRepresentation * container;
};


template <typename IndexMap>
struct DenseElementValueCoefficientIterator
        : public boost::transform_iterator<DenseElementToValueCoefficientTransformer<IndexMap>, boost::counting_iterator<std::size_t> >
{
    DenseElementValueCoefficientIterator(const DenseRepresentation & container, const IndexMap & idxMap = IndexMap(), std::size_t pos = 0)
        : boost::transform_iterator<DenseElementToValueCoefficientTransformer<IndexMap>, boost::counting_iterator<std::size_t> >(boost::counting_iterator<std::size_t>(pos), DenseElementToValueCoefficientTransformer<IndexMap>(container, idxMap))
    {
    }
};



template <typename IndexMap>
class DenseRepresentationValueCoefficientIterator
        : public boost::iterator_facade<
        DenseRepresentationValueCoefficientIterator<IndexMap>,
        ValueCoefficientPair,
        boost::forward_traversal_tag,
        ValueCoefficientPair
        >
{
public:
    typedef DenseRepresentation container_type;

    explicit DenseRepresentationValueCoefficientIterator(IndexMap map = IndexMap());
    explicit DenseRepresentationValueCoefficientIterator(const container_type& x, IndexMap map = IndexMap());
    DenseRepresentationValueCoefficientIterator(const container_type & x, std::size_t curPos, IndexMap map = IndexMap());

    bool equal(const DenseRepresentationValueCoefficientIterator & rhs) const;
    void increment();
    void decrement();
    void advance(int n);

    ValueCoefficientPair operator*() const;
    TemporaryPointerProxy<ValueCoefficientPair> operator->() const;

private:
    const container_type * container;
    std::size_t pos;
    IndexMap indexMap;
};



template <typename IndexMap>
struct DenseRepresentationAdder
{
    explicit DenseRepresentationAdder(DenseRepresentation & x, const IndexMap & map = IndexMap());
    void operator()(const ValueCoefficientPair & vcp) const;

protected:
    DenseRepresentation * container;
    IndexMap indexMap;
};



} // internal namespace
} // ext namespace
} // namespace gf2Algebra

#include "denseRepresentationIterator.hxx"

#endif // GF2ALGEBRA_EXT_INTERNAL_DENSEREPRESENTATIONITERATOR_HPP
