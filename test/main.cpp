/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include <iostream>

#include <gf2Algebra/representation.hpp>
#include <gf2Algebra/identityIndexMap.hpp>
#include <gf2Algebra/operations/addition.hpp>
#include <gf2Algebra/operations/additionAssignment.hpp>
#include <gf2Algebra/operations/multiply.hpp>
#include <gf2Algebra/io.hpp>

using namespace gf2Algebra;



int main()
{
    SparseRepresentation a, b, tgt;
    a.push_back(ValueCoefficientPair(Z2k(1), GaloisField(4)));
    a.push_back(ValueCoefficientPair(Z2k(2), GaloisField(3)));
    a.push_back(ValueCoefficientPair(Z2k(3), GaloisField(7)));
    a.push_back(ValueCoefficientPair(Z2k(7), GaloisField(2)));

    b.push_back(ValueCoefficientPair(Z2k(1), GaloisField(4)));
    b.push_back(ValueCoefficientPair(Z2k(2), GaloisField(6)));
    b.push_back(ValueCoefficientPair(Z2k(4), GaloisField(6)));
    b.push_back(ValueCoefficientPair(Z2k(7), GaloisField(4)));

    DenseRepresentation tgt2(1<<3);

    multiply(a, b, tgt);
    multiply_FFT(3, a, b, tgt2, IdentityIndexMap());

    std::cout << streamify(tgt) << std::endl;
    std::cout << std::endl;
    std::cout << streamify(tgt2, IdentityIndexMap()) << std::endl;


}


