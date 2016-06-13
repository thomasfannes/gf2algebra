/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/


#ifndef GF2ALGEBRA_IO_HPP
#define GF2ALGEBRA_IO_HPP

#include "sparseElement.hpp"
#include <ostream>

namespace gf2Algebra {

std::ostream & operator << (std::ostream & out, const SparseElement & s);

} // namespace gf2Algebra

#endif // GF2ALGEBRA_IO_HPP
