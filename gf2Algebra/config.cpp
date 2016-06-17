/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "config.hpp"
#include <limits>

namespace gf2Algebra {

std::size_t getMaximalKValue()
{
    // set the minimal value based on l
    std::size_t minK = 1<<(L_VALUE-3);

    // set the minimal value based on the K_SIGNED_TYPE type, i.e., no_bits-1 (signed)
    minK = std::min(minK, (sizeof(K_SIGNED_TYPE) * 8) - 1);

    // set the minimal value based on the K2_SIGNED_TYPE type, i.e, (no_bits-1)/2 (signed)
    minK = std::min(minK, ((sizeof(K2_SIGNED_TYPE) * 8) - 1)/2);

    // set the minimal value based on the K_UNSIGNED_TYPE type (no_bits)
    minK = std::min(minK, sizeof(K_UNSIGNED_TYPE) * 8);

    return minK;
}

} // gf2Algebra namespace
