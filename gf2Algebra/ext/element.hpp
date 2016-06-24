/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_EXT_ELEMENT_HPP
#define GF2ALGEBRA_EXT_ELEMENT_HPP


#include "../dynamicElementStorageType.hpp"
#include "representation.hpp"

#include <boost/variant.hpp>

namespace gf2Algebra {
namespace ext {

class Element
{
public:
    typedef SparseRepresentation Sparse;
    typedef DenseRepresentation Dense;
    typedef boost::variant<SparseRepresentation, DenseRepresentation> variant_type;

    Element();
    Element(const Bitset & activeBits, DynamicElementStorageType type);
    Element(const Element & other, DynamicElementStorageType storageType);

    bool operator==(const Element & rhs) const;
    bool operator!=(const Element & rhs) const;

    void reset();

    // information function
    const variant_type & variant() const;
    const Bitset & activeBits() const;
    bool isZero() const;
    std::size_t nonZeroCount() const;

    // gf2^lZ2k altering
    void setCoefficient(const Z2k & value, const GaloisField & coefficient);
    GaloisField coefficient(const Z2k & value) const;
    bool valueInActiveBits(const Z2k & value) const;


    // type functions
    DynamicElementStorageType type() const;
    void changeType(DynamicElementStorageType type);
    variant_type & variant();


private:
    static void reset(variant_type & value, DynamicElementStorageType type, const Bitset & activeBits);
    friend void swap(Element & el1, Element & el2);

    variant_type value_;
    DynamicElementStorageType type_;
    Bitset activeBits_;
};

std::ostream & operator<<(std::ostream & stream, const Element & element);

} // namespace ext
} // namespace gf2Algebra

#endif // GF2ALGEBRA_EXT_ELEMENT_HPP
