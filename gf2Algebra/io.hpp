/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/


#ifndef GF2ALGEBRA_IO_HPP
#define GF2ALGEBRA_IO_HPP

#include <ostream>
#include "config.hpp"
#include "iterator.hpp"

namespace gf2Algebra {
namespace internal {

template <typename value_coefficient_iterator>
struct ElementStreamer
{
    explicit ElementStreamer(const std::pair<value_coefficient_iterator, value_coefficient_iterator> & r)
        : range(r) {}

    std::pair<value_coefficient_iterator, value_coefficient_iterator> range;
};

template <typename value_coefficient_iterator>
std::ostream & operator<<(std::ostream & str, const ElementStreamer<value_coefficient_iterator> & streamer)
{
    bool first = true;

    for(value_coefficient_iterator it = streamer.range.first; it != streamer.range.second; ++it)
    {
        if(it->coefficient == GaloisField::zero)
            continue;

        if(first)
            first = false;
        else
            str << " + ";

        str << "(" << it->coefficient.polyRepresentation() << ") " << it->value.binaryRepresentation();
    }

    return str;
}

} // internal namespace


inline internal::ElementStreamer<SparseRepresentation::const_iterator>
streamify(const SparseRepresentation & representation)
{
    return internal::ElementStreamer<SparseRepresentation::const_iterator>(make_value_coefficient_input_range(representation));
}

template <typename IndexMap>
internal::ElementStreamer<internal::DenseRepresentationListConstIterator<IndexMap> >
streamify(const std::pair<DenseRepresentation, IndexMap> & representation)
{
    return streamify(representation.first, representation.second);
}

template <typename IndexMap>
internal::ElementStreamer<internal::DenseRepresentationListConstIterator<IndexMap> >
streamify(const DenseRepresentation & representation, const IndexMap & indexMap)
{
    return internal::ElementStreamer<internal::DenseRepresentationListConstIterator<IndexMap> >(make_value_coefficient_input_range(representation, indexMap));
}


} // namespace gf2Algebra

#endif // GF2ALGEBRA_IO_HPP
