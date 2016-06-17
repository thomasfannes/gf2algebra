/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_INTERNAL_DENSEREPRESENTATIONITERATOR_HPP
#define GF2ALGEBRA_INTERNAL_DENSEREPRESENTATIONITERATOR_HPP

#include "temporaryPointerProxy.hpp"
#include "storedCoefficientProxy.hpp"
#include "../representation.hpp"

#include <boost/iterator/iterator_facade.hpp>


namespace gf2Algebra {
namespace internal {

template <typename Representation, typename IndexMap, typename Container>
class DenseRepresentationListIteratorBase
        : public boost::iterator_facade<
        DenseRepresentationListIteratorBase<Representation, IndexMap, Container>,
        Representation,
        boost::forward_traversal_tag,
        Representation
        >
{
public:
    explicit DenseRepresentationListIteratorBase(IndexMap map = IndexMap());
    explicit DenseRepresentationListIteratorBase(Container & x, IndexMap map = IndexMap());
    DenseRepresentationListIteratorBase(Container & x, std::size_t curPos, IndexMap map = IndexMap());

    bool equal(const DenseRepresentationListIteratorBase & rhs) const;
    void increment();
    void decrement();
    void advance(int n);

    Representation operator*() const;
    TemporaryPointerProxy<Representation> operator->() const;

private:
    Container * container;
    std::size_t pos;
    IndexMap indexMap;
};

template <typename IndexMap>
struct DenseRepresentationListIterator
        : public DenseRepresentationListIteratorBase<StoredCoefficientProxy, IndexMap, DenseRepresentation>
{
    typedef DenseRepresentationListIteratorBase<StoredCoefficientProxy, IndexMap, DenseRepresentation> Base;

    explicit DenseRepresentationListIterator(IndexMap map = IndexMap())                                         : Base(map) {}
    explicit DenseRepresentationListIterator(DenseRepresentation & x, IndexMap map = IndexMap())                : Base(x, map) {}
    DenseRepresentationListIterator(DenseRepresentation & x, std::size_t curPos, IndexMap map = IndexMap())     : Base(x, curPos, map) {}
};

template <typename IndexMap>
struct DenseRepresentationListConstIterator
        : public DenseRepresentationListIteratorBase<ValueCoefficientPair, IndexMap, const DenseRepresentation>
{
    typedef DenseRepresentationListIteratorBase<ValueCoefficientPair, IndexMap, const DenseRepresentation> Base;

    explicit DenseRepresentationListConstIterator(IndexMap map = IndexMap())                                                : Base(map) {}
    explicit DenseRepresentationListConstIterator(const DenseRepresentation & x, IndexMap map = IndexMap())                 : Base(x, map) {}
    DenseRepresentationListConstIterator(const DenseRepresentation & x, std::size_t curPos, IndexMap map = IndexMap())      : Base(x, curPos, map) {}
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
} // namespace gf2Algebra

#include "denseRepresentationIterator.hxx"

#endif // GF2ALGEBRA_INTERNAL_DENSEREPRESENTATIONITERATOR_HPP
