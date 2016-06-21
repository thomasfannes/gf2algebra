/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_CONFIG_HPP
#define GF2ALGEBRA_CONFIG_HPP

#include <utility>
#include "gf256.hpp"

namespace gf2Algebra {


/**
    * Our algebra needs to able to represent up to 2^k elements of GF(2^l), where k and l are connected as follows:
    *    l >= ceil(log_2(k) + 3)
    *
    * We have chosen to fix l to 8. This implies that our field is GF(256),
    * that k can maximally be 32 and one algebra element can take up to 2^32 bytes ~ 4GB.
    *
    * If you want to change the value for l, make sure you change the following parameters:
    */

typedef GF256 GaloisField;
static const std::size_t L_VALUE = GaloisField::POWER;

/**
    * Also you will need to change the method:
    *    GF_TYPE convert_from_polynomial(DensePolynomial<2*L_VALUE, K2_SIGNED_TYPE> & polynomial)
    *
    * defined in transformation.cpp, and plug in an irreducible polynomial of degree L_VALUE
    */

/**
    * By implementation specifics, we need to perform arithmetics on the integral numbers in the range
    *  - [-0, 2^k]            ->K_UNSIGNED_TYPE
    *  - [-2^k, 2^k]         -> K_SIGNED_TYPE
    *  - [-2^(2k), 2^(2k)]   -> K2_SIGNED_TYPE
    *
    * Based on the maximal required size of k and the machine type, different possibilities are possible
    * we set a default as follows:
    */


typedef unsigned int        K_UNSIGNED_TYPE;
typedef int                 K_SIGNED_TYPE;
typedef long int            K2_SIGNED_TYPE;

static const std::size_t MAX_K_VALUE = 31;

/**
    * On the current machine, this implies an upper bound for k to be 31
    */

/**
    * If you change the values, you can always use the below function to get the maximal value of k
    */

std::size_t getMaximalKValue();

} // gf2Algebra namespace


#endif // GF2ALGEBRA_CONFIG_HPP
