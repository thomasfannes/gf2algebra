/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/


#include "operations.hpp"
#include <algorithm>
#include <cassert>

namespace gf2Algebra {

SparseElement add(const SparseElement & s1, const SparseElement & s2)
{
    assert(s1.isValid() && s2.isValid());

    if(s1.isZero())	return s2;
    if(s2.isZero())	return s1;

    SparseElement result;

    // browse sorted vectors of coefficients of each element
    typedef SparseElement::const_iterator eit;
    typedef SparseElement::sparse_coefficient sparse_coefficient;

    for (std::pair<eit, eit> it(s1.begin(), s2.begin()); !(it.first == s1.end() && it.second == s2.end());)
    {
        if(it.first == s1.end())
        {
            result.push_back((*it.second));
            it.second++;
        }

        else if (it.second == s2.end())
        {
            result.push_back((*it.first));
            it.first++;
        }
        else
        {
            const sparse_coefficient & sc1 = *it.first;
            const sparse_coefficient & sc2 = *it.second;

            if(sc1.value < sc2.value)
            {
                result.push_back(sc1);
                ++it.first;
            }
            else if(sc2.value < sc2.value)
            {
                result.push_back(sc2);
                ++it.second;
            }
            else
            {
                // both coefficient are non zeros
                sparse_coefficient sum = sc1 + sc2;
                if(!sum.isZero())
                    result.push_back(sum);

                it.first++;
                it.second++;
            }
        }
    }

    assert(result.isValid());
    return result;
}

SparseElement multiplySparse(const SparseElement & s1, const SparseElement & s2)
{
    typedef SparseElement::const_iterator cit;
    typedef SparseElement::sparse_coefficient sparse_coefficient;

    assert(s1.isValid() && s2.isValid());

    if(s1.isZero())	return SparseElement();
    if(s2.isZero())	return SparseElement();



    SparseElement products;
    // first step : multiply of the terms and store the non zero ones in the vector
    for(cit it1 = s1.begin(); it1 != s1.end(); it1++)
    {
        for(cit it2 = s2.begin(); it2 != s2.end(); it2++)
        {
            sparse_coefficient c = *it1 * *it2;
            if(!c.isZero())
                products.push_back(c);
        }
    }

    // sort the terms according to their indices
    std::sort(products.begin(), products.end());

    // add the coefficients of same indices
    SparseElement result;

    bool first = true;
    sparse_coefficient sum;
    for(cit it = products.begin(); it != products.end(); it++)
    {
        const sparse_coefficient & c = *it;

        if(first)
        {
            sum = c;
            first = false;
        }
        else
        {
            if(c.value == sum.value)
            {
                sum += c;
            }
            else
            {
                if(!sum.isZero())
                    result.push_back(sum);

                sum = c;
            }
        }
    }

    assert(result.isValid());

    return result;
}

DenseElement add(const DenseElement & d1, const DenseElement & d2)
{
    assert(d1.size() == d2.size() && d1.k() == d2.k());

    DenseElement result(d1.k());
    for(std::size_t i = 0; i < d1.size(); ++i)
        result[i] = d1[i] + d2[i];

    return result;


}

DenseElement multiplyDense(const DenseElement & d1, const DenseElement & d2)
{
    assert(d1.size() == d2.size() && d1.k() == d2.k());

    DenseElement result(d1.k());
    for(std::size_t i = 0; i < d1.size(); ++i)
    {
        Z2k p1(i);

        for(std::size_t j = 0; j < d1.size(); ++j)
        {
            Z2k p2(j);

            result[(p1*p2).getValue()] = d1[i] * d2[i];
        }
    }

    return result;
}

SemiDenseElement add(const SemiDenseElement &s1, const SemiDenseElement &s2)
{
    assert(s1.size() == s2.size() && s1.k() == s2.k() && s1.bitInfo() == s2.bitInfo());

    SemiDenseElement result(s1.k(), s1.bitInfo().unusedBits());
    for(std::size_t i = 0; i < s1.size(); ++i)
        result[i] = s1[i] + s2[i];

    return result;
}

SemiDenseElement multiplySemiDense(const SemiDenseElement &s1, const SemiDenseElement &s2)
{
    assert(s1.size() == s2.size() && s1.k() == s2.k() && s1.bitInfo() == s2.bitInfo());

    return result;
}


} // namespace gf2Algebra

