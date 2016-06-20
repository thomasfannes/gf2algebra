/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "util.hpp"
#include <cstdlib>
#include <gf2Algebra/iterator.hpp>
#include <gf2Algebra/identityIndexMap.hpp>

using namespace gf2Algebra;

template <typename OutputIterator>
void fill(OutputIterator out, std::size_t noValues, std::size_t valueMask)
{
    for(std::size_t i = 0; i < noValues; ++i)
        *out++ = ValueCoefficientPair( Z2k(std::rand() & valueMask), GaloisField(std::rand() & 255) );
}

std::pair<DenseRepresentation, IdentityIndexMap> generateRandom(unsigned char k, std::size_t noValues, DenseTag)
{

    std::size_t maxVal = (1<<k);
    std::pair<DenseRepresentation, IdentityIndexMap> rep;
    initialize(rep.first, k);

    fill(make_ordered_value_coefficient_output_iterator(rep.first, rep.second), noValues, maxVal - 1);

    return rep;
}

SparseRepresentation generateRandom(unsigned char k, std::size_t noValues, SparseTag)
{
    gf2Algebra::SparseRepresentation rep;
    fill(make_unordered_value_coefficient_output_iterator(rep), noValues, (1<<k) - 1);

    return rep;
}


gf2Algebra::SparseRepresentation transform(const gf2Algebra::SparseRepresentation & representation, unsigned int /*k*/)
{
    return representation;
}

std::pair<gf2Algebra::DenseRepresentation, gf2Algebra::IdentityIndexMap> transform(const gf2Algebra::SparseRepresentation &representation, unsigned char k)
{
    std::pair<gf2Algebra::DenseRepresentation, gf2Algebra::IdentityIndexMap> res;
    gf2Algebra::initialize(res.first, k);

    gf2Algebra::makeDense(representation, res);
    return res;
}

std::pair<gf2Algebra::DenseRepresentation, gf2Algebra::IdentityIndexMap> transform(const std::pair<gf2Algebra::DenseRepresentation, gf2Algebra::IdentityIndexMap> & representation, unsigned int /*k*/)
{
    return representation;
}

gf2Algebra::SparseRepresentation transform(const std::pair<gf2Algebra::DenseRepresentation, gf2Algebra::IdentityIndexMap> &representation, unsigned char k)
{
    gf2Algebra::SparseRepresentation res;
    gf2Algebra::initialize(res, k);

    gf2Algebra::makeSparse(representation, res);
    return res;
}
