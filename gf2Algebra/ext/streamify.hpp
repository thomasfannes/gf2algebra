/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_STREAMIFY_HPP
#define GF2ALGEBRA_EXT_STREAMIFY_HPP

#include "representation.hpp"

#include <ostream>

namespace gf2Algebra {
namespace ext {


namespace internal {

template <typename value_coefficient_input_iterator>
struct StreamWriter
{
    explicit StreamWriter(const std::pair<value_coefficient_input_iterator, value_coefficient_input_iterator> & r)
        : range(r) {}

    std::pair<value_coefficient_input_iterator, value_coefficient_input_iterator> range;
};


template <typename value_coefficient_iterator>
std::ostream & operator<<(std::ostream & str, const StreamWriter<value_coefficient_iterator> & streamer);

} // internal namespace


template <typename Representation, typename IndexMap>
internal::StreamWriter<typename representation_iterator_traits<Representation, IndexMap>::value_coefficient_input_iterator>
streamify(
        const Representation & representation,
        const IndexMap & indexMap,
        typename boost::enable_if<is_representation<Representation> >::type * /*dummy*/ = 0
        );

} // ext namespace
} // namespace gf2Algebra

#include "streamify.hxx"

#endif // GF2ALGEBRA_EXT_STREAMIFY_HPP
