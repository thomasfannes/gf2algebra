/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_ITERATOR_HPP
#define GF2ALGEBRA_ITERATOR_HPP

#include "representation.hpp"
#include "internal/denseRepresentationIterator.hpp"
#include "internal/sparseRepresentationIterator.hpp"
#include <boost/function_output_iterator.hpp>

namespace gf2Algebra {

inline std::pair<SparseRepresentation::const_iterator, SparseRepresentation::const_iterator>
make_value_coefficient_input_range(const SparseRepresentation & representation)
{
    return std::make_pair(representation.begin(), representation.end());
}

template <typename IndexMap>
inline std::pair<internal::DenseRepresentationListConstIterator<IndexMap>, internal::DenseRepresentationListConstIterator<IndexMap> >
make_value_coefficient_input_range(const DenseRepresentation & representation, const IndexMap & indexMap)
{
    return std::make_pair(
        internal::DenseRepresentationListConstIterator<IndexMap>(representation, indexMap),
        internal::DenseRepresentationListConstIterator<IndexMap>(representation, representation.size(), indexMap)
                );
}


template <typename IndexMap>
inline std::pair<internal::DenseRepresentationListConstIterator<IndexMap>, internal::DenseRepresentationListConstIterator<IndexMap> >
make_value_coefficient_input_range(const std::pair<DenseRepresentation, IndexMap> & representation)
{
    return std::make_pair(
        internal::DenseRepresentationListConstIterator<IndexMap>(representation.first, representation.second),
        internal::DenseRepresentationListConstIterator<IndexMap>(representation.first, representation.first.size(), representation.second)
                );
}


inline boost::function_output_iterator<internal::SparseRepresentationOrderedAdder>
make_ordered_value_coefficient_output_iterator(SparseRepresentation & representation)
{
    return boost::make_function_output_iterator(internal::SparseRepresentationOrderedAdder(representation));
}

inline boost::function_output_iterator<internal::SparseRepresentationUnorderedAdder>
make_unordered_value_coefficient_output_iterator(SparseRepresentation & representation)
{
    return boost::make_function_output_iterator(internal::SparseRepresentationUnorderedAdder(representation));
}

template <typename IndexMap>
boost::function_output_iterator<internal::DenseRepresentationAdder<IndexMap> >
make_ordered_value_coefficient_output_iterator(DenseRepresentation & representation, const IndexMap & indexMap)
{
    return boost::make_function_output_iterator(internal::DenseRepresentationAdder<IndexMap>(representation, indexMap));
}


template <typename IndexMap>
boost::function_output_iterator<internal::DenseRepresentationAdder<IndexMap> >
make_ordered_value_coefficient_output_iterator(std::pair<DenseRepresentation, IndexMap> & representation)
{
    return boost::make_function_output_iterator(internal::DenseRepresentationAdder<IndexMap>(representation.first, representation.second));
}

} // gf2Algebra namespace

#endif // GF2ALGEBRA_ITERATOR_HPP
