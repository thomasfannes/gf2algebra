/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "z2k.hpp"
#include <boost/lexical_cast.hpp>
#include <bitset>

namespace gf2Algebra {

Z2k::Z2k()
    : val_(0)
{
}

Z2k::Z2k(std::size_t val)
    : val_(val)
{
}

Z2k Z2k::operator*(const Z2k & rhs) const
{
    return Z2k(val_ ^ rhs.val_);
}

bool Z2k::operator<(const Z2k & rhs) const
{
    return val_ < rhs.val_;
}

bool Z2k::operator==(const Z2k & rhs) const
{
    return val_ == rhs.val_;
}

bool Z2k::operator!=(const Z2k & rhs) const
{
    return val_ != rhs.val_;
}

std::size_t Z2k::getValue() const
{
    return val_;
}

std::string Z2k::numRepresentation() const
{
    return boost::lexical_cast<std::string>(val_);
}

std::string Z2k::binaryRepresentation() const
{
    return std::bitset<32>(val_).to_string();
}

void swap(Z2k & lhs, Z2k & rhs)
{
    using std::swap;
    swap(lhs.val_, rhs.val_);
}

} // namespace gf2Algebra
