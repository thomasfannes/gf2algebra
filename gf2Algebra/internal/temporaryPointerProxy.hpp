/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_INTERNAL_TEMPORARYPOINTERPROXY_HPP
#define GF2ALGEBRA_INTERNAL_TEMPORARYPOINTERPROXY_HPP

namespace gf2Algebra {
namespace internal {

template <typename T>
struct TemporaryPointerProxy
{
    TemporaryPointerProxy(const T & t)
        : t_(t)
    {
    }

    T * operator->() { return &t_; }
    const T * operator->() const { return &t_; }

    T t_;
};

} // internal namespace
} // gf2Algebra namespace

#endif // GF2ALGEBRA_INTERNAL_TEMPORARYPOINTERPROXY_HPP
