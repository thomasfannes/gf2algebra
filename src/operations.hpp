/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/


#ifndef GF2ALGEBRA_OPERATIONS_HPP
#define GF2ALGEBRA_OPERATIONS_HPP

#include "sparseElement.hpp"


namespace gf2Algebra {

SparseElement add(const SparseElement & s1, const SparseElement & s2);
SparseElement multiplySparse(const SparseElement & s1, const SparseElement & s2);

} // namespace gf2Algebra

#endif // GF2ALGEBRA_OPERATIONS_HPP
