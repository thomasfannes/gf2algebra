/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef UTIL_HPP
#define UTIL_HPP

#include <gf2Algebra/representation.hpp>
#include <gf2Algebra/identityIndexMap.hpp>
#include <gf2Algebra/io.hpp>
#include <boost/test/framework.hpp>

struct DenseTag {};
struct SparseTag {};

std::pair<gf2Algebra::DenseRepresentation, gf2Algebra::IdentityIndexMap> generateRandom(unsigned char k, std::size_t noValues, DenseTag);
gf2Algebra::SparseRepresentation generateRandom(unsigned char k, std::size_t noValues, SparseTag);

template <typename iterator>
bool checkZero(std::pair<iterator, iterator> p)
{
    while(p.first != p.second)
        if((*p.first++).coefficient != gf2Algebra::GaloisField::zero)
            return false;

    return true;
}

template <typename lhs_iterator, typename rhs_iterator>
bool checkEqual(std::pair<lhs_iterator, lhs_iterator> lhs, std::pair<rhs_iterator, rhs_iterator> rhs)
{
    while(lhs.first != lhs.second && rhs.first != rhs.second)
    {
        if(lhs.first->value < rhs.first->value)
        {
            if((*lhs.first++).coefficient != gf2Algebra::GaloisField::zero)
                return false;
        }
        else if(rhs.first->value < lhs.first->value)
        {
            if((*rhs.first++).coefficient != gf2Algebra::GaloisField::zero)
                return false;
        }
        else
        {
            if((*lhs.first++).coefficient != (*rhs.first++).coefficient)
                return false;
        }

    }

    return checkZero(lhs) && checkZero(rhs);
}

#endif // UTIL_HPP
