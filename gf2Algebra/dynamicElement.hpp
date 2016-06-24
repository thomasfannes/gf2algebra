#ifndef GF2ALGEBRA_DYNAMICELEMENT_HPP
#define GF2ALGEBRA_DYNAMICELEMENT_HPP

#include <boost/shared_ptr.hpp>
#include "z2k.hpp"
#include "config.hpp"
#include "dynamicElementStorageType.hpp"

namespace gf2Algebra {

class DynamicElement
{
    class Impl;

public:
    // constructor
    DynamicElement();
    explicit DynamicElement(const Bitset & activeBits, DynamicElementStorageType storage = SparseStorage);
    DynamicElement(const DynamicElement & element);

    // operators
    DynamicElement & operator=(const DynamicElement & rhs);
    DynamicElement & operator+=(const DynamicElement & rhs);
    DynamicElement operator+(const DynamicElement & rhs) const;
    DynamicElement operator*(const DynamicElement & rhs) const;
    DynamicElement multiply(const DynamicElement & rhs, const Bitset & targetBits) const;
    bool operator==(const DynamicElement & rhs) const;
    bool operator!=(const DynamicElement & rhs) const;

    // alteration methods
    void setCoefficient(const Z2k & value, const GaloisField & coefficient);
    GaloisField coefficient(const Z2k & value) const;

    // information methods
    bool isZero() const;
    std::size_t nonZeroCount() const;

    void reset();
    DynamicElementStorageType storageType() const;
    void changeStorageType(DynamicElementStorageType newType);


private:
    void makeUniqueIfNecessary();
    friend void swap(DynamicElement & lhs, DynamicElement & rhs);
    friend std::ostream & operator<<(std::ostream & stream, const DynamicElement & element);

    boost::shared_ptr<Impl> d_;
};



} // namespace gf2Algebra

#endif // GF2ALGEBRA_DYNAMICELEMENT_HPP
