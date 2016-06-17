/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "representation.hpp"

namespace gf2Algebra {

bool isZero(const SparseRepresentation & representation)
{
    return representation.empty();
}

bool isZero(const DenseRepresentation & representation)
{
    for(std::size_t i = 0; i < representation.size(); ++i)
        if(representation[i] != GaloisField::zero)
            return false;

    return true;
}

std::size_t countNonZero(const SparseRepresentation & representation)
{
    return representation.size();
}

std::size_t countNonZero(const DenseRepresentation & representation)
{
    std::size_t cnt = 0;
    for(std::size_t i = 0; i < representation.size(); ++i)
        if(representation[i] != GaloisField::zero)
            ++cnt;

    return cnt;
}

void initialize(DenseRepresentation & representation, std::size_t k)
{
    representation.assign((1<<k), GaloisField::zero);
}


void initialize(SparseRepresentation & representation, std::size_t /*k*/)
{
    representation.clear();
}

void reset(DenseRepresentation & representation)
{
    representation.assign(representation.size(), GaloisField::zero);
}

void reset(SparseRepresentation & representation)
{
    representation.clear();
}


} // gf2Algebra namespace
