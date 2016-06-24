/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_REPRESENTATION_HXX
#define GF2ALGEBRA_EXT_REPRESENTATION_HXX

#include "representation.hpp"

namespace gf2Algebra {
namespace ext {

inline bool isZero(const SparseRepresentation & representation)
{
    return representation.empty();
}

inline std::size_t countNonZero(const SparseRepresentation & representation)
{
    return representation.size();
}

inline void initialize(DenseRepresentation & representation, unsigned char k)
{
    representation.assign((1<<k), GaloisField::zero);
}


inline void initialize(SparseRepresentation & representation)
{
    representation.clear();
}

inline void reset(DenseRepresentation & representation)
{
    representation.assign(representation.size(), GaloisField::zero);
}

inline void reset(SparseRepresentation & representation)
{
    representation.clear();
}


} // ext namespace
} // gf2Algebra namespace

#endif // GF2ALGEBRA_EXT_REPRESENTATION_HXX
