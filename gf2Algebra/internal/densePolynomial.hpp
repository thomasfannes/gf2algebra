/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_INTERNAL_DENSEPOLYNOMIAL_HPP
#define GF2ALGEBRA_INTERNAL_DENSEPOLYNOMIAL_HPP

#include <vector>

namespace gf2Algebra {
namespace internal {




template <std::size_t DEGREE, typename COEFFICIENT_TYPE>
class DensePolynomial
{
public:
    typedef COEFFICIENT_TYPE coefficient_type;
    enum { degree = DEGREE };

    // constructors and assignment operator
    DensePolynomial();
    DensePolynomial(const DensePolynomial & rhs);
    DensePolynomial & operator=(const DensePolynomial & rhs);

    // alteration methods
    void setCoefficient(std::size_t position, const coefficient_type & coeff);
    const coefficient_type & coeffientAt(std::size_t position) const;
    coefficient_type & coeffientAt(std::size_t position);

    // operators
    DensePolynomial<DEGREE, COEFFICIENT_TYPE> & operator+=(const DensePolynomial<DEGREE, COEFFICIENT_TYPE> & rhs);
    DensePolynomial<DEGREE, COEFFICIENT_TYPE> & operator-=(const DensePolynomial<DEGREE, COEFFICIENT_TYPE> & rhs);
    DensePolynomial<DEGREE, COEFFICIENT_TYPE> operator+(const DensePolynomial<DEGREE, COEFFICIENT_TYPE> & rhs) const;
    DensePolynomial<DEGREE, COEFFICIENT_TYPE> operator-(const DensePolynomial<DEGREE, COEFFICIENT_TYPE> & rhs) const;
    DensePolynomial<2*DEGREE, COEFFICIENT_TYPE> operator*(const DensePolynomial<DEGREE, COEFFICIENT_TYPE> & rhs) const;

    // scalar operations
    DensePolynomial<DEGREE, COEFFICIENT_TYPE> & operator*=(const COEFFICIENT_TYPE & scalar);
    DensePolynomial<DEGREE, COEFFICIENT_TYPE> & operator/=(const COEFFICIENT_TYPE & scalar);
    DensePolynomial<DEGREE, COEFFICIENT_TYPE> operator*(const COEFFICIENT_TYPE & scalar) const;
    DensePolynomial<DEGREE, COEFFICIENT_TYPE> operator/(const COEFFICIENT_TYPE & scalar) const;

    DensePolynomial<DEGREE, COEFFICIENT_TYPE> & operator<<=(unsigned char shift);
    DensePolynomial<DEGREE, COEFFICIENT_TYPE> & operator>>=(unsigned char shift);
    DensePolynomial<DEGREE, COEFFICIENT_TYPE> operator<<(unsigned char shift) const;
    DensePolynomial<DEGREE, COEFFICIENT_TYPE> operator>>(unsigned char shift) const;

    template <std::size_t NDEGREE, typename COEFFTYPE>
    friend void swap(DensePolynomial<NDEGREE, COEFFTYPE> & p1, DensePolynomial<NDEGREE, COEFFTYPE> & p2);

private:
    std::vector<coefficient_type> coeffients_;
};

template <std::size_t TDEGREE, typename TCOEFFTYPE, std::size_t LDEGREE, typename LCOEFFTYPE, std::size_t RDEGREE, typename RCOEFFTYPE>
DensePolynomial<TDEGREE, TCOEFFTYPE>
dense_polynomial_multiply(const DensePolynomial<LDEGREE, LCOEFFTYPE> & lhs, const DensePolynomial<RDEGREE, RCOEFFTYPE> & rhs);


} // internal namespace
} // namespace gf2Algebra

#include "densePolynomial.hxx"

#endif // GF2ALGEBRA_INTERNAL_DENSEPOLYNOMIAL_HPP
