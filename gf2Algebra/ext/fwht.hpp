/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_FWHT_HPP
#define GF2ALGEBRA_EXT_FWHT_HPP

#include <vector>
#include "densePolynomial.hpp"

namespace gf2Algebra {
namespace ext {

template <typename DataType> void fwht(std::vector<DataType> & elements, std::size_t k);
template <typename DataType> void fwht(std::vector<DataType> & elements);


} // ext namespace
} // namespace gf2Algebra

#include "fwht.hxx"

#endif // GF2ALGEBRA_EXT_FWHT_HPP
