/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_INTERNAL_FWHT_HPP
#define GF2ALGEBRA_INTERNAL_FWHT_HPP

#include <vector>
#include "../config.hpp"
#include "densePolynomial.hpp"

namespace gf2Algebra {
namespace internal {


typedef DensePolynomial<L_VALUE, K_SIGNED_TYPE> POLY_L_K;
typedef DensePolynomial<2*L_VALUE, K2_SIGNED_TYPE> POLY_2L_2K;

POLY_L_K convert_to_polynomial(const GaloisField & coeff);
GaloisField convert_from_polynomial(POLY_2L_2K & polynomial);
POLY_2L_2K multiply_polynomials(const POLY_L_K & lhs, const POLY_L_K & rhs);


bool isPowerOfTwo(std::size_t number);
std::size_t iLog2(std::size_t value);

template <typename DataType> void fwht_radix2(std::vector<DataType> & elements, std::size_t firstPosition, std::size_t size);
template <typename DataType> void fwht(std::vector<DataType> & elements, std::size_t k);
template <typename DataType> void fwht(std::vector<DataType> & elements);

} // internal namespace
} // namespace gf2Algebra

#include "fwht.hxx"

#endif // GF2ALGEBRA_INTERNAL_FWHT_HPP
