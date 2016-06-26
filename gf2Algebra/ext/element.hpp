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
    Element(const Element & other);
    Element(const Element & other, DynamicElementStorageType storageType);
    Element(const Element & other, const Bitset & bitsToKeep);
    Element(const Element & other, const Bitset & bitsToKeep, DynamicElementStorageType storageType);
    Element(const Element & other, const Bitmap & srcToTgtMap);
    Element(const Element & other, const Bitmap & srcToTgtMap, DynamicElementStorageType storageType);

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

    // bit transformation functions
    void aggregateBits(const Bitset & bitsToKeep, DynamicElementStorageType storageType);
    void aggregateBits(const Bitset & bitsToKeep);
    void changeDimensionality(const Bitmap & srcToTgtMap, DynamicElementStorageType storageType);
    void changeDimensionality(const Bitmap & srcToTgtMap);


    // type functions
    DynamicElementStorageType type() const;
    void changeType(DynamicElementStorageType type);
    variant_type & variant();


private:
    void int_aggregateBits(const variant_type & src, variant_type & tgt, const Bitset & srcBitset, Bitset & tgtBitset, const Bitset &bitsToKeep, DynamicElementStorageType storageType) const;
    void int_changeDimensionality(const variant_type & src, variant_type & tgt, const Bitset & srcBitset, Bitset & tgtBitset, const Bitmap & srcToTgtMap, DynamicElementStorageType storageType) const;

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
