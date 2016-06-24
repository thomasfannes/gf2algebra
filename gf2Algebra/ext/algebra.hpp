/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_ALGEBRA_HPP
#define GF2ALGEBRA_EXT_ALGEBRA_HPP

#include "element.hpp"


namespace gf2Algebra {
namespace ext {

class Algebra
{
public:
    typedef Element element_type;

    // let V_a be the set of active bits in an element a, and let n_a be the number of non-zero coefficients in a.
    // If n_a < c * sqrt(2^|V_a|), then the element is stored using a sparse representation, otherwise a dense representation is used.
    const static double DEFAULT_C = 1.0;

    // let a and b be two elements of our algebra, V_a, V_b respectively be the sets of active bits in a and b.
    // if 2^(|V_a| + |V_b| - |V_a \cup V_b|) < n * |V_a \cup V_b|, then quadratic multiplication is used.
    // Otherwise the FFT is used. Note that if a or b are sparse, then the quadratic multiplication is used.
    const static double DEFAULT_N = 56;


    explicit Algebra(double c = DEFAULT_C, double n = DEFAULT_N);

    void add(const element_type & lhs, const element_type & rhs, element_type & tgt) const;
    void addAssign(element_type & lhs, const element_type & rhs) const;

    void multiply(const element_type & lhs, const element_type & rhs, element_type & tgt) const;
    void multiply(const element_type & lhs, const element_type & rhs, element_type & tgt, Bitset requiredTgtBits) const;

private:
    void updateRepresentation(element_type & element) const;
    bool useFFT(unsigned char leftK, unsigned char rightK, unsigned char joinK) const;
    DynamicElementStorageType calculatePreferredRepresentationStorageType(const element_type & element) const;

private:
    double c;
    double n;
};


} // namespace ext
} // namespace gf2Algebra

#endif // GF2ALGEBRA_EXT_ALGEBRA_HPP
