/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef UTIL_HPP
#define UTIL_HPP

#include <gf2Algebra/ext/element.hpp>

void initializeElement(
        gf2Algebra::ext::Element & element,
        const gf2Algebra::Bitset & activeBits,
        std::size_t noElements
        );


#endif // UTIL_HPP
