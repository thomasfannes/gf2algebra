/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_Z2K_HPP
#define GF2ALGEBRA_Z2K_HPP

#include <utility>
#include <string>

namespace gf2Algebra {

class Z2k
{
public:
    Z2k();
    explicit Z2k(std::size_t val);

    Z2k operator*(const Z2k & rhs) const;
    bool operator<(const Z2k & rhs) const;
    bool operator==(const Z2k & rhs) const;
    bool operator!=(const Z2k & rhs) const;

    friend void swap(Z2k & lhs, Z2k & rhs);

    std::size_t getValue() const;

    std::string numRepresentation() const;
    std::string binaryRepresentation() const;

private:
    std::size_t val_;
};

} // namespace gf2Algebra

#endif // GF2ALGEBRA_Z2K_HPP
