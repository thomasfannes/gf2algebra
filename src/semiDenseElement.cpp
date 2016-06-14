/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "semiDenseElement.hpp"

namespace gf2Algebra {
namespace config {


SemiDenseElementConfig::BitInfo::BitInfo()
{
}

SemiDenseElementConfig::BitInfo::BitInfo(const std::set<unsigned char> & unusedBits)
{
}

bool SemiDenseElementConfig::BitInfo::hasIndex(group_type value) const
{
}

SemiDenseElementConfig::index_type SemiDenseElementConfig::BitInfo::toIndex(group_type value) const
{
}

SemiDenseElementConfig::group_type SemiDenseElementConfig::BitInfo::fromIndex(index_type index) const
{
}

bool SemiDenseElementConfig::BitInfo::operator==(const BitInfo & rhs) const
{
}

std::set<unsigned char> SemiDenseElementConfig::BitInfo::unusedBits() const
{
}

} // config namespace

SemiDenseElement::SemiDenseElement()
    : Base(1, field_type::zero)
    , k_(0)
{
}

SemiDenseElement::SemiDenseElement(unsigned char k, const std::set<unsigned char> & unusedBits)
    : Base(1 << (k - unusedBits.size()),  field_type::zero)
    , k_(0)
    , bitInfo_(unusedBits)
{
}

bool SemiDenseElement::isZero() const
{
    for(const_iterator it = begin(); it != end(); ++it)
        if(*it != field_type::zero)
            return false;

    return true;
}

std::size_t SemiDenseElement::countNonZero() const
{
    std::size_t cnt = 0;
    for(const_iterator it = begin(); it != end(); ++it)
        if(*it != field_type::zero)
            ++cnt;

    return cnt;
}

unsigned char SemiDenseElement::k() const
{
    return k_;
}

} // namespace gf2Algebra
