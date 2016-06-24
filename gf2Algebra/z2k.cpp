/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "z2k.hpp"
#include <boost/lexical_cast.hpp>
#include <bitset>

namespace gf2Algebra {

std::string Z2k::numRepresentation() const
{
    return boost::lexical_cast<std::string>(val_);
}

std::string Z2k::binaryRepresentation() const
{
    return std::bitset<sizeof(storage_type)*8>(val_).to_string();
}

std::ostream & operator<<(std::ostream & stream, const Z2k & value)
{
    stream << value.getValue();
    return stream;
}

} // namespace gf2Algebra
