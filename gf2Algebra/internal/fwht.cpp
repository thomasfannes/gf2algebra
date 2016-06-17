/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "fwht.hpp"

namespace gf2Algebra {
namespace internal {



bool isPowerOfTwo(std::size_t number)
{
    return number > 0 && !(number & (number-1) );
}

std::size_t iLog2(std::size_t value)
{
    std::size_t log = 0;
    for(; value != 0; value >>= 1)
        ++log;

    return log-1;
}

#define SET_COEFF(POS) p.setCoefficient(POS, ((val >> POS) & 1))

POLY_L_K convert_to_polynomial(const GaloisField &coeff)
{
    POLY_L_K p;
    unsigned char val = coeff.integralRepresentation();

    for(std::size_t i = 0; i < L_VALUE; ++i)
        SET_COEFF(i);

    return p;
}

GaloisField convert_from_polynomial(POLY_2L_2K & polynomial)
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

POLY_2L_2K multiply_polynomials(const POLY_L_K & lhs, const POLY_L_K & rhs)
{
    return dense_polynomial_multiply<2*L_VALUE, K2_SIGNED_TYPE>(lhs, rhs);
}

} // internal namespace
} // gf2Algebra namespace
