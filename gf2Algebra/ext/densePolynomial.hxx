/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_DENSEPOLYNOMIAL_HXX
#define GF2ALGEBRA_EXT_DENSEPOLYNOMIAL_HXX

#include "densePolynomial.hpp"
#include <cassert>

namespace gf2Algebra {
namespace ext {

#define TDEF template <std::size_t DEGREE, typename COEFFICIENT_TYPE>
#define CDEF DensePolynomial<DEGREE, COEFFICIENT_TYPE>

TDEF
CDEF::DensePolynomial()
    : coeffients_(DEGREE, coefficient_type())
{
}

TDEF
CDEF::DensePolynomial(const DensePolynomial & rhs)
    : coeffients_(rhs.coeffients_)
{
}

TDEF
CDEF & CDEF::operator=(const DensePolynomial & rhs)
{
    using std::swap;

    DensePolynomial tmp(rhs);
    swap(*this, tmp);

    return *this;
}

// alteration methods
TDEF
void CDEF::setCoefficient(std::size_t position, const coefficient_type & coeff)
{
    assert(position < degree);
    coeffients_[position] = coeff;
}

TDEF
const typename CDEF::coefficient_type & CDEF::coeffientAt(std::size_t position) const
{
    assert(position < degree);
    return coeffients_[position];
}

TDEF
typename CDEF::coefficient_type & CDEF::coeffientAt(std::size_t position)
{
    assert(position < degree);
    return coeffients_[position];
}

// operators
TDEF
CDEF & CDEF::operator+=(const CDEF & rhs)
{
    for(std::size_t i = 0; i < degree; ++i)
        coeffients_[i] += rhs.coeffients_[i];

    return *this;
}

TDEF
CDEF & CDEF::operator-=(const CDEF & rhs)
{
    for(std::size_t i = 0; i < degree; ++i)
        coeffients_[i] -= rhs.coeffients_[i];

    return *this;
}

TDEF
CDEF CDEF::operator+(const CDEF & rhs) const
{
    DensePolynomial p(*this);
    p += rhs;
    return p;
}

TDEF
CDEF CDEF::operator-(const CDEF & rhs) const
{
    DensePolynomial p(*this);
    p -= rhs;
    return p;
}

TDEF
CDEF & CDEF::operator*=(const COEFFICIENT_TYPE & scalar)
{
    for(std::size_t i = 0; i < degree; ++i)
        coeffients_[i] *= scalar;

    return *this;
}

TDEF
CDEF & CDEF::operator/=(const COEFFICIENT_TYPE & scalar)
{
    for(std::size_t i = 0; i < degree; ++i)
        coeffients_[i] /= scalar;

    return *this;
}

TDEF
CDEF CDEF::operator*(const COEFFICIENT_TYPE & scalar) const
{
    DensePolynomial p(*this);
    p *= scalar;

    return p;
}

TDEF
CDEF CDEF::operator/(const COEFFICIENT_TYPE & scalar) const
{
    DensePolynomial p(*this);
    p /= scalar;

    return p;
}


TDEF
CDEF & CDEF::operator<<=(unsigned char shift)
{
    for(std::size_t i = 0; i < degree; ++i)
        coeffients_[i] <<= shift;

    return *this;
}

TDEF
CDEF & CDEF::operator>>=(unsigned char shift)
{
    for(std::size_t i = 0; i < degree; ++i)
        coeffients_[i] >>= shift;

    return *this;
}

TDEF
CDEF CDEF::operator<<(unsigned char shift) const
{
    DensePolynomial p(*this);
    p <<= shift;

    return p;
}

TDEF
CDEF CDEF::operator>>(unsigned char shift) const
{
    DensePolynomial p(*this);
    p >>= shift;

    return p;
}

TDEF
DensePolynomial<2*DEGREE, COEFFICIENT_TYPE> CDEF::operator*(const CDEF & rhs) const
{
    return dense_polynomial_multiply<2*DEGREE, COEFFICIENT_TYPE>(*this, rhs);
}

TDEF
void swap(CDEF & p1, CDEF & p2)
{
    std::swap(p1.coeffients_, p2.coeffients_);
}

namespace internal {

template <std::size_t TDEGREE, typename TCOEFFTYPE, std::size_t LDEGREE, typename LCOEFFTYPE, std::size_t RDEGREE, typename RCOEFFTYPE>
DensePolynomial<TDEGREE, TCOEFFTYPE>
dense_polynomial_multiply_complete(const DensePolynomial<LDEGREE, LCOEFFTYPE> & lhs, const DensePolynomial<RDEGREE, RCOEFFTYPE> & rhs)
{
    DensePolynomial<TDEGREE, TCOEFFTYPE> result;
    for(std::size_t l = 0; l < lhs.degree; ++l)
        for(std::size_t r = 0; r < rhs.degree; ++r)
            result.coeffientAt(l+r) += (lhs.coeffientAt(l)*rhs.coeffientAt(r));

    return result;
}

template <std::size_t TDEGREE, typename TCOEFFTYPE, std::size_t LDEGREE, typename LCOEFFTYPE, std::size_t RDEGREE, typename RCOEFFTYPE>
DensePolynomial<TDEGREE, TCOEFFTYPE>
dense_polynomial_multiply_limited(const DensePolynomial<LDEGREE, LCOEFFTYPE> & lhs, const DensePolynomial<RDEGREE, RCOEFFTYPE> & rhs)
{
    DensePolynomial<TDEGREE, TCOEFFTYPE> result;
    for(std::size_t l = 0; l < lhs.degree; ++l)
        for(std::size_t r = 0; r < rhs.degree && l+r < TDEGREE; ++r)
            result.coeffientAt(l+r) += (lhs.coeffientAt(l)*rhs.coeffientAt(r));

    return result;
}

}

template <std::size_t TDEGREE, typename TCOEFFTYPE, std::size_t LDEGREE, typename LCOEFFTYPE, std::size_t RDEGREE, typename RCOEFFTYPE>
DensePolynomial<TDEGREE, TCOEFFTYPE>
dense_polynomial_multiply(const DensePolynomial<LDEGREE, LCOEFFTYPE> & lhs, const DensePolynomial<RDEGREE, RCOEFFTYPE> & rhs)
{
    if(TDEGREE < LDEGREE + RDEGREE)
        return internal::dense_polynomial_multiply_limited<TDEGREE, TCOEFFTYPE>(lhs, rhs);
    else
        return internal::dense_polynomial_multiply_complete<TDEGREE, TCOEFFTYPE>(lhs, rhs);
}

#undef TDEF
#undef CDEF

} // ext namespace
} // namespace gf2Algebra

#endif // GF2ALGEBRA_EXT_DENSEPOLYNOMIAL_HXX
