/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_Z2K_HPP
#define GF2ALGEBRA_Z2K_HPP

#include <utility>
#include <string>
#include "config.hpp"

namespace gf2Algebra
{

class Z2k
{
public:
    typedef gf2Algebra::K_UNSIGNED_TYPE         storage_type;

    Z2k()                                       : val_(0) {}
    explicit Z2k(storage_type val)              : val_(val) {}
    Z2k(const Z2k & rhs)                        : val_(rhs.val_) {}

    Z2k & operator=(const Z2k & rhs)            { if (this != &rhs) {Z2k tmp(rhs); swap(*this, tmp); } return *this; }

    Z2k operator*(const Z2k & rhs) const        { return Z2k(val_ ^ rhs.val_); }
    bool operator<(const Z2k & rhs) const       { return val_ < rhs.val_; }
    bool operator==(const Z2k & rhs) const      { return val_ == rhs.val_; }
    bool operator!=(const Z2k & rhs) const      { return val_ != rhs.val_; }

    friend void swap(Z2k & lhs, Z2k & rhs)      { std::swap(lhs.val_, rhs.val_); }

    storage_type getValue() const               { return val_; }

    std::string numRepresentation() const;
    std::string binaryRepresentation() const;

private:

    storage_type val_;
};

} // namespace gf2Algebra

#endif // GF2ALGEBRA_Z2K_HPP
