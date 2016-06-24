/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_DENSEPOLYNOMIALIO_HPP
#define GF2ALGEBRA_EXT_DENSEPOLYNOMIALIO_HPP

#include "densePolynomial.hpp"
#include <ostream>
#include <string>
#include <sstream>


namespace gf2Algebra {
namespace ext {

template <std::size_t D, typename CT>
std::ostream & operator<<(std::ostream & str, const DensePolynomial<D, CT> & polynomial)
{
    bool first = true;

    for(int degree = D-1; degree >= 0; --degree)
    {
        // a non-zero coeff
        if(polynomial.coeffientAt(degree) != CT())
        {
            if(first)
                first = false;
            else
                str << " + ";

            str << polynomial.coeffientAt(degree);
            if(degree != 0)
                str << "{x^" << degree << "}";
        }
    }

    if(first)
        str << CT();

    return str;
}

template <std::size_t D, typename CT>
std::string dense_polynomial_to_string(const DensePolynomial<D, CT> & polynomial)
{
    std::stringstream str;
    str << polynomial;

    return str.str();
}

} // ext namespace
} // gf2Algebra namespace

#endif // GF2ALGEBRA_EXT_DENSEPOLYNOMIALIO_HPP
