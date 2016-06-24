/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "representation.hpp"

namespace gf2Algebra {
namespace ext {

bool isZero(const DenseRepresentation & representation)
{
    for(std::size_t i = 0; i < representation.size(); ++i)
        if(representation[i] != GaloisField::zero)
            return false;

    return true;
}

std::size_t countNonZero(const DenseRepresentation & representation)
{
    std::size_t cnt = 0;
    for(std::size_t i = 0; i < representation.size(); ++i)
        if(representation[i] != GaloisField::zero)
            ++cnt;

    return cnt;
}


} // ext namespace
} // gf2Algebra namespace
