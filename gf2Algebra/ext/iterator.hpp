/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_ITERATOR_HPP
#define GF2ALGEBRA_EXT_ITERATOR_HPP

#include "representation.hpp"
#include "internal/denseRepresentationIterator.hpp"
#include "internal/sparseRepresentationIterator.hpp"
#include "internal/z2kMaskFunctor.hpp"
#include <boost/function_output_iterator.hpp>

namespace gf2Algebra {
namespace ext {

template <typename Representation, typename IndexMap>
struct representation_iterator_traits;

template <typename IndexMap>
struct representation_iterator_traits<SparseRepresentation, IndexMap>
{
    typedef internal::SparseElementValueCoefficientIterator<IndexMap>                                   value_coefficient_input_iterator;

    typedef internal::SparseRepresentationOrderedAdder<IndexMap>                                        ordered_adder;
    typedef internal::SparseRepresentationUnorderedAdder<IndexMap>                                      unordered_adder;

    typedef boost::function_output_iterator<ordered_adder >                                             ordered_value_coefficient_output_iterator;
    typedef boost::function_output_iterator<unordered_adder>                                            unordered_value_coefficient_output_iterator;
    typedef boost::function_output_iterator< internal::Z2kMaskFunctor<unordered_adder > >               masked_unordered_value_coefficient_output_iterator;
};


template <typename IndexMap>
struct representation_iterator_traits<DenseRepresentation, IndexMap>
{
    typedef internal::DenseElementValueCoefficientIterator<IndexMap>                                    value_coefficient_input_iterator;

    typedef internal::DenseRepresentationAdder<IndexMap>                                                ordered_adder;
    typedef internal::DenseRepresentationAdder<IndexMap>                                                unordered_adder;

    typedef boost::function_output_iterator<ordered_adder >                                             ordered_value_coefficient_output_iterator;
    typedef boost::function_output_iterator<unordered_adder>                                            unordered_value_coefficient_output_iterator;
    typedef boost::function_output_iterator< internal::Z2kMaskFunctor<unordered_adder > >               masked_unordered_value_coefficient_output_iterator;
};


template <typename IndexMap>
std::pair<
    typename representation_iterator_traits<SparseRepresentation, IndexMap>::value_coefficient_input_iterator,
    typename representation_iterator_traits<SparseRepresentation, IndexMap>::value_coefficient_input_iterator
>
make_value_coefficient_input_range(const SparseRepresentation &representation, const IndexMap &indexMap)
{
    return std::make_pair(
                internal::SparseElementValueCoefficientIterator<IndexMap>(representation.begin(), indexMap),
                internal::SparseElementValueCoefficientIterator<IndexMap>(representation.end(), indexMap)
                );
}


template <typename IndexMap>
std::pair<
    typename representation_iterator_traits<DenseRepresentation, IndexMap>::value_coefficient_input_iterator,
    typename representation_iterator_traits<DenseRepresentation, IndexMap>::value_coefficient_input_iterator
>
make_value_coefficient_input_range(const DenseRepresentation &representation, const IndexMap & indexMap)
{
    return std::make_pair(
                internal::DenseElementValueCoefficientIterator<IndexMap>(representation, indexMap, 0),
                internal::DenseElementValueCoefficientIterator<IndexMap>(representation, indexMap, representation.size())
                );
}


template <typename IndexMap>
typename representation_iterator_traits<SparseRepresentation, IndexMap>::ordered_value_coefficient_output_iterator
make_ordered_value_coefficient_output_iterator(SparseRepresentation &representation, const IndexMap &indexMap)
{
    return boost::make_function_output_iterator(internal::SparseRepresentationOrderedAdder<IndexMap>(representation, indexMap));
}

template <typename IndexMap>
typename representation_iterator_traits<SparseRepresentation, IndexMap>::unordered_value_coefficient_output_iterator
make_unordered_value_coefficient_output_iterator(SparseRepresentation &representation, const IndexMap &indexMap)
{
    return boost::make_function_output_iterator(internal::SparseRepresentationUnorderedAdder<IndexMap>(representation, indexMap));
}


template <typename IndexMap>
typename representation_iterator_traits<DenseRepresentation, IndexMap>::ordered_value_coefficient_output_iterator
make_ordered_value_coefficient_output_iterator(DenseRepresentation &representation, const IndexMap &indexMap)
{
    return boost::make_function_output_iterator(internal::DenseRepresentationAdder<IndexMap>(representation, indexMap));
}


template <typename IndexMap>
typename representation_iterator_traits<DenseRepresentation, IndexMap>::unordered_value_coefficient_output_iterator
make_unordered_value_coefficient_output_iterator(DenseRepresentation &representation, const IndexMap &indexMap)
{
    return boost::make_function_output_iterator(internal::DenseRepresentationAdder<IndexMap>(representation, indexMap));
}



template <typename IndexMap>
typename representation_iterator_traits<SparseRepresentation, IndexMap>::masked_unordered_value_coefficient_output_iterator
make_unordered_value_coefficient_output_iterator(SparseRepresentation &representation, const IndexMap &indexMap, Z2k::storage_type mask)
{
    return boost::make_function_output_iterator(
                internal::make_mask_function(
                    mask,
                    internal::SparseRepresentationUnorderedAdder<IndexMap>(representation, indexMap)
                    )
                );
}

template <typename IndexMap>
typename representation_iterator_traits<DenseRepresentation, IndexMap>::masked_unordered_value_coefficient_output_iterator
make_unordered_value_coefficient_output_iterator(DenseRepresentation &representation, const IndexMap &indexMap, Z2k::storage_type mask)
{
    return boost::make_function_output_iterator(
                internal::make_mask_function(
                    mask,
                    internal::DenseRepresentationAdder<IndexMap>(representation, indexMap)
                    )
                );
}

} // ext namespace
} // gf2Algebra namespace

#endif // GF2ALGEBRA_EXT_INTERNAL_ITERATOR_HPP
