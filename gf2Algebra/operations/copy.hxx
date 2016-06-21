#ifndef GF2ALGEBRA_OPERATIONS_COPY_HXX
#define GF2ALGEBRA_OPERATIONS_COPY_HXX

#include "copy.hpp"
#include "../iterator.hpp"

namespace gf2Algebra {
namespace internal {

template <typename input_iterator, typename output_iterator>
void int_copy(std::pair<input_iterator, input_iterator> src, output_iterator tgt)
{
    std::copy(src.first, src.second, tgt);
}


} // internal namespace

inline void copy(const SparseRepresentation & source, SparseRepresentation & target)
{
    target = source;
}

template <typename TgtIndexMap>
void copy(
        const SparseRepresentation & source,
        std::pair<DenseRepresentation, TgtIndexMap> & target)
{
    internal::int_copy(
                make_value_coefficient_input_range(source),
                make_ordered_value_coefficient_output_iterator(target)
                );
}

template <typename SrcIndexMap>
void copy(
        const std::pair<DenseRepresentation, SrcIndexMap> & source,
        SparseRepresentation & target)
{
    internal::int_copy(
                make_value_coefficient_input_range(source),
                make_ordered_value_coefficient_output_iterator(target)
                );
}

template <typename SrcIndexMap, typename TgtIndexMap>
void copy(
        const std::pair<DenseRepresentation, SrcIndexMap> & source,
        std::pair<DenseRepresentation, TgtIndexMap> & target)
{
    internal::int_copy(
                make_value_coefficient_input_range(source),
                make_ordered_value_coefficient_output_iterator(target)
                );
}

template <>
void copy(
        const std::pair<DenseRepresentation, IdentityIndexMap> & source,
        std::pair<DenseRepresentation, IdentityIndexMap> & target
        )
{
    target = source;
}

}

#endif // GF2ALGEBRA_OPERATIONS_COPY_HXX

