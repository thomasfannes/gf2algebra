#ifndef GF2ALGEBRA_EXT_INTERNAL_DYNAMICVISITORS_HPP
#define GF2ALGEBRA_EXT_INTERNAL_DYNAMICVISITORS_HPP

#include <boost/variant/static_visitor.hpp>
#include "../copy.hpp"
#include "../addition.hpp"
#include "../additionAssignment.hpp"
#include "../multiplication.hpp"
#include "../equal.hpp"
#include "../streamify.hpp"
#include "../groupTransformation.hpp"

#include "../subsetIndexMap.hpp"
#include "../identityIndexMap.hpp"


namespace gf2Algebra {
namespace ext {

namespace internal {

template <typename IndexMap1, typename IndexMap2>
struct change_dimensionality_visit : public boost::static_visitor<>
{
    change_dimensionality_visit(const Bitset & srcActiveBits, const Bitset & tgtActiveBits, const Bitmap & srcToTgtMap)
        : srcIndexMap(srcActiveBits),
          tgtIndexMap(tgtActiveBits),
          transformer(srcToTgtMap)
    {
    }

    template <typename T1, typename T2>
    void operator()(const T1 & src, T2 & tgt) const
    {
        change_dimensionality(src, tgt, srcIndexMap, tgtIndexMap, transformer);
    }

    IndexMap1 srcIndexMap;
    IndexMap2 tgtIndexMap;
    BitMapTransformer transformer;
};

template <typename IndexMap1, typename IndexMap2>
struct aggregate_bits_visit : public boost::static_visitor<>
{
    aggregate_bits_visit(const Bitset & srcActiveBits, const Bitset & tgtActiveBits, Z2k::storage_type nMask)
        : srcIndexMap(srcActiveBits),
          tgtIndexMap(tgtActiveBits),
          mask(nMask)
    {
    }

    template <typename T1, typename T2>
    void operator()(const T1 & src, T2 & tgt) const
    {
        aggregate_bits(src, tgt, srcIndexMap, tgtIndexMap, mask);
    }

    IndexMap1 srcIndexMap;
    IndexMap2 tgtIndexMap;
    Z2k::storage_type mask;
};

struct set_coefficient_visit : public boost::static_visitor<>
{
    set_coefficient_visit(const Z2k & v, const GaloisField & c, const Bitset & activeBits)
        : value(v),
          coefficient(c),
          indexMap(activeBits)
    {
    }

    void operator()(DenseRepresentation & representation ) const
    {
        representation[indexMap.fromGroupValue(value)] = coefficient;
    }

    void operator()(SparseRepresentation & representation) const
    {
        SparseElement el(indexMap.fromGroupValue(value), coefficient);
        SparseRepresentation::iterator it = std::lower_bound(representation.begin(), representation.end(), el, compare_on_index);

        if(it == representation.end() || it->first != el.first)
            representation.insert(it, el);
        else
            *it = el;
    }

    Z2k value;
    GaloisField coefficient;
    SubsetIndexMap indexMap;
};


struct get_coefficient_visit : public boost::static_visitor<GaloisField>
{
    get_coefficient_visit(const Z2k & v, const Bitset & activeBits)
        : value(v),
          indexMap(activeBits)
    {
    }

    GaloisField operator()(const DenseRepresentation & representation ) const
    {
        return representation[indexMap.fromGroupValue(value)];
    }

    GaloisField operator()(const SparseRepresentation & representation) const
    {
        SparseElement el(indexMap.fromGroupValue(value), GaloisField::zero);
        SparseRepresentation::const_iterator it = std::lower_bound(representation.begin(), representation.end(), el, compare_on_index);

        if(it == representation.end() || it->first != el.first)
            return GaloisField::zero;
        else
            return it->second;
    }

    Z2k value;
    SubsetIndexMap indexMap;
};


template <typename vcp_iterator, typename IndexMap>
struct insert_vcp_stream_visit : public boost::static_visitor<>
{
    insert_vcp_stream_visit(vcp_iterator first, vcp_iterator last, const Bitset & activeBits)
        : range(first, last),
          indexMap(activeBits)
    {
    }

    template <typename T> void operator()(T & element) const
    {
        typename representation_iterator_traits<T, IndexMap>::unordered_value_coefficient_output_iterator
                out = make_unordered_value_coefficient_output_iterator(element, indexMap);

        for(vcp_iterator it = range.first; it != range.second; ++it)
            *out++ = *it;
    }

    std::pair<vcp_iterator, vcp_iterator> range;
    IndexMap indexMap;
};

template <typename IndexMap>
struct ostream_visit : public boost::static_visitor<>
{
    ostream_visit(std::ostream & stream, const Bitset & activeBits) : str(&stream), indexMap(activeBits) { }

    template <typename T> void operator()(const T & element) const
    {
        (*str) << streamify(element, indexMap);
    }
    std::ostream * str;
    IndexMap indexMap;
};

template <typename IndexMap1, typename IndexMap2>
struct equal_visit : public boost::static_visitor<bool>
{
    equal_visit(const Bitset & lhsActiveBits, const Bitset & rhsActiveBits)
        : lhsIndexMap(lhsActiveBits),
          rhsIndexMap(rhsActiveBits)
    {
    }

    template <typename T1, typename T2>
    bool operator()(const T1 & lhs, const T2 & rhs) const
    {
        return gf2Algebra::ext::equal(lhs, rhs, lhsIndexMap, rhsIndexMap);
    }

    IndexMap1 lhsIndexMap;
    IndexMap2 rhsIndexMap;
};

struct copy_visit : public boost::static_visitor<>
{
    template <typename T1, typename T2>
    void operator()(const T1 & src, T2 & tgt) const
    {
        gf2Algebra::ext::copy(src, tgt, IdentityIndexMap(), IdentityIndexMap());
    }
};

struct count_non_zero_visit : public boost::static_visitor<std::size_t>
{
    template <typename T>
    std::size_t operator()(const T & element) const
    {
        return countNonZero(element);
    }
};

struct is_zero_visitor : public boost::static_visitor<bool>
{
    template <typename T> bool operator()(const T & element) const
    {
        return isZero(element);
    }
};

template <typename IndexMap1, typename IndexMap2>
struct add_visit : public boost::static_visitor<>
{
    add_visit(const Bitset & lhsBitset, const Bitset & rhsBitset)
        : lhsIndexMap(lhsBitset),
          rhsIndexMap(rhsBitset)
    {
    }

    template <typename T1, typename T2, typename T3>
    void operator()(const T1 & lhs, const T2 & rhs, T3 & tgt) const
    {
        gf2Algebra::ext::add(lhs, rhs, tgt, lhsIndexMap, rhsIndexMap, IdentityIndexMap());
    }

    IndexMap1 lhsIndexMap;
    IndexMap2 rhsIndexMap;
};

template <typename IndexMap2>
struct add_assign_visit : public boost::static_visitor<>
{
    add_assign_visit(const Bitset & rhsBitSet)
        : rhsIndexMap(rhsBitSet)
    {
    }

    template <typename T1, typename T2>
    void operator()(T1 & lhs, const T2 & rhs) const
    {
        gf2Algebra::ext::addAssign(lhs, rhs, IdentityIndexMap(), rhsIndexMap);
    }

    IndexMap2 rhsIndexMap;
};


template <typename IndexMap1, typename IndexMap2, typename IndexMap3>
struct multiply_fft_mask_visit : public boost::static_visitor<>
{
    multiply_fft_mask_visit(const Bitset & lhsBitset, const Bitset & rhsBitset, const Bitset & tgtBitset, Z2k::storage_type nMask, unsigned char nK)
        : lhsIndexMap(lhsBitset),
          rhsIndexMap(rhsBitset),
          tgtIndexMap(tgtBitset),
          mask(nMask),
          k(nK)
    {
    }

    template <typename T1, typename T2, typename T3>
    void operator()(const T1 & lhs, const T2 & rhs, T3 & tgt) const
    {
        gf2Algebra::ext::multiply_FFT(k, lhs, rhs, tgt, mask, lhsIndexMap, rhsIndexMap, tgtIndexMap);
    }

    IndexMap1 lhsIndexMap;
    IndexMap2 rhsIndexMap;
    IndexMap3 tgtIndexMap;
    Z2k::storage_type mask;
    unsigned char k;
};

template <typename IndexMap1, typename IndexMap2, typename IndexMap3>
struct multiply_fft_visit : public boost::static_visitor<>
{
    multiply_fft_visit(const Bitset & lhsBitset, const Bitset & rhsBitset, const Bitset & tgtBitset, unsigned char nK)
        : lhsIndexMap(lhsBitset),
          rhsIndexMap(rhsBitset),
          tgtIndexMap(tgtBitset),
          k(nK)
    {
    }

    template <typename T1, typename T2, typename T3>
    void operator()(const T1 & lhs, const T2 & rhs, T3 & tgt) const
    {
        gf2Algebra::ext::multiply_FFT(k, lhs, rhs, tgt, lhsIndexMap, rhsIndexMap, tgtIndexMap);
    }

    IndexMap1 lhsIndexMap;
    IndexMap2 rhsIndexMap;
    IndexMap3 tgtIndexMap;
    unsigned char k;
};


template <typename IndexMap1, typename IndexMap2, typename IndexMap3>
struct multiply_quadratic_mask_visit : public boost::static_visitor<>
{
    multiply_quadratic_mask_visit(const Bitset & lhsBitset, const Bitset & rhsBitset, const Bitset & tgtBitset, Z2k::storage_type nMask)
        : lhsIndexMap(lhsBitset),
          rhsIndexMap(rhsBitset),
          tgtIndexMap(tgtBitset),
          mask(nMask)
    {
    }

    template <typename T1, typename T2, typename T3>
    void operator()(const T1 & lhs, const T2 & rhs, T3 & tgt) const
    {
        gf2Algebra::ext::multiply_quadratic(lhs, rhs, tgt, mask, lhsIndexMap, rhsIndexMap, tgtIndexMap);
    }

    IndexMap1 lhsIndexMap;
    IndexMap2 rhsIndexMap;
    IndexMap3 tgtIndexMap;
    Z2k::storage_type mask;
};


template <typename IndexMap1, typename IndexMap2, typename IndexMap3>
struct multiply_quadratic_visit : public boost::static_visitor<>
{
    multiply_quadratic_visit(const Bitset & lhsBitset, const Bitset & rhsBitset, const Bitset & tgtBitset)
        : lhsIndexMap(lhsBitset),
          rhsIndexMap(rhsBitset),
          tgtIndexMap(tgtBitset)
    {
    }

    template <typename T1, typename T2, typename T3>
    void operator()(const T1 & lhs, const T2 & rhs, T3 & tgt) const
    {
        gf2Algebra::ext::multiply_quadratic(lhs, rhs, tgt, lhsIndexMap, rhsIndexMap, tgtIndexMap);
    }

    IndexMap1 lhsIndexMap;
    IndexMap2 rhsIndexMap;
    IndexMap3 tgtIndexMap;
};

} // internal namespace
} // ext namespace
} // gf2Algebra namespace

#endif // GF2ALGEBRA_EXT_INTERNAL_DYNAMICVISITORS_HPP

