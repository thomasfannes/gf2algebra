/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_OPERATIONS_MULTIPLICATION_HXX
#define GF2ALGEBRA_OPERATIONS_MULTIPLICATION_HXX

#include "multiplication.hpp"
#include "../iterator.hpp"
#include "../internal/fwht.hpp"
#include "../internal/densePolynomialIO.hpp"

namespace gf2Algebra {
namespace internal {

template <typename lhs_iterator, typename rhs_iterator, typename output_iterator>
void element_wise_multiply(const std::pair<lhs_iterator, lhs_iterator> & lhs, const std::pair<rhs_iterator, rhs_iterator> & rhs, output_iterator out)
{
    // compute the quadratic product
    for(lhs_iterator lit = lhs.first; lit != lhs.second; ++lit)
    {
        const ValueCoefficientPair & l = *lit;

        // zero coefficients can be skipped
        if(l.coefficient == GaloisField::zero)
            continue;

        for(rhs_iterator rit = rhs.first; rit != rhs.second; ++rit)
        {
            const ValueCoefficientPair & r = *rit;

            // zero coefficients can be skipped
            if(r.coefficient == GaloisField::zero)
                continue;


            // check for a non-zero result, and add to the list
            const ValueCoefficientPair & res = l*r;
            if(res.coefficient != GaloisField::zero)
                *out++ = res;
        }
    }
}

template <typename iterator>
void fillPolyVector(std::pair<iterator, iterator> values, std::vector<POLY_L_K> & tgt)
{
    for(; values.first != values.second; ++values.first)
    {
        const ValueCoefficientPair & p = *values.first;
        tgt[p.value.getValue()] = convert_to_polynomial(p.coefficient);
    }
}


template <typename lhs_iterator, typename rhs_iterator, typename output_iterator>
void fft_multiply(unsigned char noBits, std::pair<lhs_iterator, lhs_iterator> lhs, std::pair<rhs_iterator, rhs_iterator> rhs, output_iterator out)
{
    // left hand side
    std::vector<POLY_L_K> l(1 << noBits);
    fillPolyVector(lhs, l);
    fwht(l, noBits);

    // right hand side
    std::vector<POLY_L_K> r(1 << noBits);
    fillPolyVector(rhs, r);
    fwht(r, noBits);

    // multiply them
    std::vector<POLY_2L_2K> t(1 << noBits);
    for(std::size_t i = 0; i < t.size(); ++i)
        t[i] = multiply_polynomials(l[i], r[i]);

    // and perform the fft
    fwht(t, noBits);

    for(std::size_t i = 0; i < t.size(); ++i)
    {
        t[i] >>= noBits;
        *out++ = ValueCoefficientPair(Z2k(i), convert_from_polynomial(t[i]));
    }
}

} // internal namespace

inline void multiply(const SparseRepresentation & lhs, const SparseRepresentation & rhs, SparseRepresentation & tgt)
{
    internal::element_wise_multiply(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_unordered_value_coefficient_output_iterator(tgt)
                );
}


template <typename TgtIndexMap>
void multiply(
        const SparseRepresentation & lhs,
        const SparseRepresentation & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{
    internal::element_wise_multiply(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

template <typename RhsIndexMap>
void multiply(
        const SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        SparseRepresentation & tgt)
{
    internal::element_wise_multiply(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_unordered_value_coefficient_output_iterator(tgt)
                );

}

template <typename RhsIndexMap, typename TgtIndexMap>
void multiply(
        const SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{
    internal::element_wise_multiply(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

template <typename LhsIndexMap>
void multiply(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs,
        SparseRepresentation & tgt)
{
    internal::element_wise_multiply(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_unordered_value_coefficient_output_iterator(tgt)
                );

}

template <typename LhsIndexMap, typename TgtIndexMap>
void multiply(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{
    internal::element_wise_multiply(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

template <typename LhsIndexMap, typename RhsIndexMap>
void multiply(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        SparseRepresentation & tgt)
{
internal::element_wise_multiply(
            make_value_coefficient_input_range(lhs),
            make_value_coefficient_input_range(rhs),
            make_unordered_value_coefficient_output_iterator(tgt)
            );
}

template <typename LhsIndexMap, typename RhsIndexMap, typename TgtIndexMap>
void multiply(
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{
    internal::element_wise_multiply(
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}


inline
void multiply_FFT(
        unsigned char noBits,
        const SparseRepresentation & lhs,
        const SparseRepresentation & rhs,
        SparseRepresentation & tgt)
{
    internal::fft_multiply(
                noBits,
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}



template <typename TgtIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const SparseRepresentation & lhs,
        const SparseRepresentation & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{
    internal::fft_multiply(
                noBits,
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

template <typename RhsIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        SparseRepresentation & tgt)
{
    internal::fft_multiply(
                noBits,
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

template <typename RhsIndexMap, typename TgtIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const SparseRepresentation & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{
    internal::fft_multiply(
                noBits,
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}

template <typename LhsIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs,
        SparseRepresentation & tgt)
{
    internal::fft_multiply(
                noBits,
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}


template <typename LhsIndexMap, typename TgtIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const SparseRepresentation & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{
    internal::fft_multiply(
                noBits,
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}


template <typename LhsIndexMap, typename RhsIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        SparseRepresentation & tgt)
{
    internal::fft_multiply(
                noBits,
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}


template <typename LhsIndexMap, typename RhsIndexMap, typename TgtIndexMap>
void multiply_FFT(
        unsigned char noBits,
        const std::pair<DenseRepresentation, LhsIndexMap> & lhs,
        const std::pair<DenseRepresentation, RhsIndexMap> & rhs,
        std::pair<DenseRepresentation, TgtIndexMap> & tgt)
{
    internal::fft_multiply(
                noBits,
                make_value_coefficient_input_range(lhs),
                make_value_coefficient_input_range(rhs),
                make_ordered_value_coefficient_output_iterator(tgt)
                );
}


} // namespace gf2Algebra


#endif // GF2ALGEBRA_OPERATIONS_MULTIPLICATION_HXX
