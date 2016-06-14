/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_DENSEELEMENT_HPP
#define GF2ALGEBRA_DENSEELEMENT_HPP

#include "gf256.hpp"
#include "z2k.hpp"
#include <vector>

namespace gf2Algebra {
namespace config {

struct DenseElementConfig
{
    typedef GF256                       field_type;
    typedef Z2k                         group_type;
    typedef std::vector<field_type>     storage_type;
    typedef storage_type::size_type     index_type;
};

} // config namespace

class DenseElement : public config::DenseElementConfig::storage_type
{
    typedef config::DenseElementConfig::storage_type Base;

public:
    typedef config::DenseElementConfig::field_type field_type;
    typedef config::DenseElementConfig::group_type group_type;

    DenseElement();
    explicit DenseElement(unsigned char k);

    bool isZero() const;
    std::size_t countNonZero() const;
    unsigned char k() const;

private:
    unsigned char k_;
};

} // namespace gf2Algebra


#endif // GF2ALGEBRA_DENSEELEMENT_HPP
