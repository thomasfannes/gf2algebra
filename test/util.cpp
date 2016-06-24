/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "util.hpp"

using namespace gf2Algebra;
using namespace gf2Algebra::ext;

void initializeElement(Element & element, const Bitset & activeBits, std::size_t noElements)
{
    for(std::size_t i = 0; i < noElements; ++i)
        element.setCoefficient(Z2k( rand() & activeBits.to_ulong() ), GaloisField( rand() & 255 ));
}
