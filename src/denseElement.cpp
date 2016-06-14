/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "denseElement.hpp"

namespace gf2Algebra {

DenseElement::DenseElement()
    : Base(1, field_type::zero)
    , k_(0)
{
}
DenseElement::DenseElement(unsigned char k)
    : Base(1 << k, field_type::zero),
      k_(k)
{
}

bool DenseElement::isZero() const
{
    for(const_iterator it = begin(); it != end(); ++it)
        if(*it != field_type::zero)
            return false;

    return true;
}

std::size_t DenseElement::countNonZero() const
{
    std::size_t cnt = 0;
    for(const_iterator it = begin(); it != end(); ++it)
        if(*it != field_type::zero)
            ++cnt;

    return cnt;
}

unsigned char DenseElement::k() const
{
    return k_;
}

} // namespace gf2Algebra
