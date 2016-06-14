/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_SEMIDENSEELEMENT_HPP
#define GF2ALGEBRA_SEMIDENSEELEMENT_HPP

#include "z2k.hpp"
#include "gf256.hpp"
#include <vector>
#include <set>

namespace gf2Algebra {
namespace config {

struct SemiDenseElementConfig
{
    typedef Z2k                         group_type;
    typedef GF256                       field_type;
    typedef std::vector<field_type>     storage_type;
    typedef storage_type::size_type     index_type;

    struct MaskAndShift
    {
        std::size_t mask;
        unsigned char shift;
    };

    struct BitInfo
    {
        BitInfo();
        explicit BitInfo(const std::set<unsigned char> & unusedBits);

        bool hasIndex(group_type value) const;
        index_type toIndex(group_type value) const;
        group_type fromIndex(index_type index) const;

        bool operator==(const BitInfo & rhs) const;
        std::set<unsigned char> unusedBits() const;

        std::size_t globalMask_;
        std::vector<MaskAndShift> maskAndShifts_;
    };
};

} // config namespace

class SemiDenseElement : public config::SemiDenseElementConfig::storage_type
{
public:
    typedef config::SemiDenseElementConfig::storage_type    Base;
    typedef config::SemiDenseElementConfig::group_type      group_type;
    typedef config::SemiDenseElementConfig::field_type      field_type;
    typedef config::SemiDenseElementConfig::BitInfo         BitInfo;

    SemiDenseElement();
    SemiDenseElement(unsigned char k, const std::set<unsigned char> & unusedBits);

    bool isZero() const;
    std::size_t countNonZero() const;
    unsigned char k() const;

    const BitInfo & bitInfo() const;

private:
    unsigned char k_;
    BitInfo bitInfo_;
};

} // namespace gf2Algebra

#endif // GF2ALGEBRA_SEMIDENSEELEMENT_HPP
