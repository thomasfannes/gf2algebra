/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_STREAMIFY_HXX
#define GF2ALGEBRA_EXT_STREAMIFY_HXX

#include "streamify.hpp"
#include "iterator.hpp"

namespace gf2Algebra {
namespace ext {
namespace internal {

template <typename value_coefficient_iterator>
std::ostream & operator<<(std::ostream & str, const StreamWriter<value_coefficient_iterator> & streamer)
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


template <typename Representation, typename IndexMap>
internal::StreamWriter<typename representation_iterator_traits<Representation, IndexMap>::value_coefficient_input_iterator>
streamify(
        const Representation & representation,
        const IndexMap & indexMap,
        typename boost::enable_if<is_representation<Representation> >::type * /*dummy*/ = 0
        )

{
    typedef typename representation_iterator_traits<Representation, IndexMap>::value_coefficient_input_iterator vcit;

    return internal::StreamWriter<vcit>(make_value_coefficient_input_range(representation, indexMap));
}


} // ext namespace
} // namespace gf2Algebra

#endif // GF2ALGEBRA_EXT_STREAMIFY_HXX
