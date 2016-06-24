/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_MULTIPLICATION_HXX
#define GF2ALGEBRA_EXT_MULTIPLICATION_HXX

#include "multiplication.hpp"
#include "densePolynomial.hpp"
#include "iterator.hpp"
#include "fwht.hpp"


namespace gf2Algebra {
namespace ext {
namespace internal {

typedef DensePolynomial<L_VALUE, K_SIGNED_TYPE> POLY_L_K;
typedef DensePolynomial<2*L_VALUE, K2_SIGNED_TYPE> POLY_2L_2K;

#define SET_COEFF(POS) p.setCoefficient(POS, ((val >> POS) & 1))

inline POLY_L_K convert_to_polynomial(const GaloisField &coeff)
{
    POLY_L_K p;
    unsigned char val = coeff.integralRepresentation();

    for(std::size_t i = 0; i < L_VALUE; ++i)
        SET_COEFF(i);

    return p;
}

inline GaloisField convert_from_polynomial(POLY_2L_2K & polynomial)
{


    // start by dividing the polynomial by the irreducible polynomial x^8 + x^4 + x^3 + x + 1
    // if you change the GF256 field, you need to plug in your own irreducible polynomial below
    for(std::size_t d = 2*L_VALUE - 1; d >= L_VALUE; --d)
    {
        K2_SIGNED_TYPE factor = polynomial.coeffientAt(d);
        polynomial.coeffientAt(d-4) -= factor;
        polynomial.coeffientAt(d-5) -= factor;
        polynomial.coeffientAt(d-7) -= factor;
        polynomial.coeffientAt(d-8) -= factor;
    }

    GaloisField::storage_type val = 0;

    for(std::size_t i = 0; i < L_VALUE; ++i)
        val |= (polynomial.coeffientAt(i) & 1) << i;

    return GaloisField(val);
}

inline POLY_2L_2K multiply_polynomials(const POLY_L_K & lhs, const POLY_L_K & rhs)
{
    return dense_polynomial_multiply<2*L_VALUE, K2_SIGNED_TYPE>(lhs, rhs);
}


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
void fft_multiply(unsigned char noBits, const std::pair<lhs_iterator, lhs_iterator> & lhs, const std::pair<rhs_iterator, rhs_iterator> & rhs, output_iterator out)
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

template <typename Rep1, typename Rep2, typename Rep3, typename IndexMap1, typename IndexMap2, typename IndexMap3>
void multiply_quadratic(
        const Rep1 & lhs,
        const Rep2 & rhs,
        Rep3 & tgt,
        const IndexMap1 & lhsIndexMap,
        const IndexMap2 & rhsIndexMap,
        const IndexMap3 & tgtIndexMap,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value && is_representation<Rep3>::value >::type * /*dummy*/
        )
{
    internal::element_wise_multiply(
                make_value_coefficient_input_range(lhs, lhsIndexMap),
                make_value_coefficient_input_range(rhs, rhsIndexMap),
                make_unordered_value_coefficient_output_iterator(tgt, tgtIndexMap)
                );
}

template <typename Rep1, typename Rep2, typename Rep3, typename IndexMap1, typename IndexMap2, typename IndexMap3>
void multiply_quadratic(
        const Rep1 & lhs,
        const Rep2 & rhs,
        Rep3 & tgt,
        Z2k::storage_type mask,
        const IndexMap1 & lhsIndexMap,
        const IndexMap2 & rhsIndexMap,
        const IndexMap3 & tgtIndexMap,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value && is_representation<Rep3>::value >::type * /*dummy*/
        )
{
    internal::element_wise_multiply(
                make_value_coefficient_input_range(lhs, lhsIndexMap),
                make_value_coefficient_input_range(rhs, rhsIndexMap),
                make_unordered_value_coefficient_output_iterator(tgt, tgtIndexMap, mask)
                );
}


template <typename Rep1, typename Rep2, typename Rep3, typename IndexMap1, typename IndexMap2, typename IndexMap3>
void multiply_FFT(
        unsigned char noBits,
        const Rep1 & lhs,
        const Rep2 & rhs,
        Rep3 & tgt,
        const IndexMap1 & lhsIndexMap,
        const IndexMap2 & rhsIndexMap,
        const IndexMap3 & tgtIndexMap,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value && is_representation<Rep3>::value >::type * /*dummy*/
        )
{
    internal::fft_multiply(
                noBits,
                make_value_coefficient_input_range(lhs, lhsIndexMap),
                make_value_coefficient_input_range(rhs, rhsIndexMap),
                make_ordered_value_coefficient_output_iterator(tgt, tgtIndexMap)
                );
}

template <typename Rep1, typename Rep2, typename Rep3, typename IndexMap1, typename IndexMap2, typename IndexMap3>
void multiply_FFT(
        unsigned char noBits,
        const Rep1 & lhs,
        const Rep2 & rhs,
        Rep3 & tgt,
        Z2k::storage_type mask,
        const IndexMap1 & lhsIndexMap,
        const IndexMap2 & rhsIndexMap,
        const IndexMap3 & tgtIndexMap,
        typename boost::enable_if_c<is_representation<Rep1>::value && is_representation<Rep2>::value && is_representation<Rep3>::value >::type * /*dummy*/
        )
{
    internal::fft_multiply(
                noBits,
                make_value_coefficient_input_range(lhs, lhsIndexMap),
                make_value_coefficient_input_range(rhs, rhsIndexMap),
                make_ordered_value_coefficient_output_iterator(tgt, tgtIndexMap, mask)
                );
}

} // ext namespace
} // namespace gf2Algebra


#endif // GF2ALGEBRA_EXT_MULTIPLICATION_HXX
