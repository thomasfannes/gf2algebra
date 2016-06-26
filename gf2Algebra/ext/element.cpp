#include "element.hpp"
#include "internal/dynamicVisitors.hpp"

namespace gf2Algebra {
namespace ext {
namespace {

std::size_t create_minimal_bitset(
        const Bitset & lhsActiveBits,
        const Bitset & rhsActiveBits,
        Bitset & minLhsSet,
        Bitset & minRhsSet)
{
    std::size_t curBit = 0;

    for(std::size_t i = 0; i < MAX_K_VALUE; ++i)
    {
        // is bit i active?
        if(lhsActiveBits[i] || rhsActiveBits[i])
        {
            // yes, so map it to bit curBit
            minLhsSet.set(curBit, lhsActiveBits[i]);
            minRhsSet.set(curBit, rhsActiveBits[i]);

            // increase the current bit
            ++curBit;
        }
    }

    return curBit;
}

} //  namespace

Element::Element()
    : value_(SparseRepresentation()),
      type_(SparseStorage)
{
    reset();
}

Element::Element(const Bitset & activeBits, DynamicElementStorageType type)
    : type_(type),
      activeBits_(activeBits)
{
    reset();
}


Element::Element(const Element & other)
    : value_(other.variant()),
      type_(other.type()),
      activeBits_(other.activeBits())
{
}

Element::Element(const Element & other, DynamicElementStorageType storageType)
    : type_(storageType),
      activeBits_(other.activeBits_)

{
    // just use the copy constructor if their type is the same
    if(type_ == other.type_)
    {
        value_ = other.value_;
        return;
    }

    // first create and initialize our value
    reset();

    // and then use the copy_visitor
    boost::apply_visitor(internal::copy_visit(), other.value_, value_);
}




Element::Element(const Element & other, const Bitset & bitsToKeep)
    : type_(other.type())
{
    int_aggregateBits(other.variant(), value_, other.activeBits(), activeBits_, bitsToKeep, type_);
}

Element::Element(const Element & other, const Bitset & bitsToKeep, DynamicElementStorageType storageType)
    : type_(storageType)
{
    int_aggregateBits(other.variant(), value_, other.activeBits(), activeBits_, bitsToKeep, type_);
}







Element::Element(const Element & other, const Bitmap & srcToTgtMap)
    : type_(other.type_)
{
    int_changeDimensionality(other.variant(), value_, other.activeBits(), activeBits_, srcToTgtMap, type_);
}

Element::Element(const Element & other, const Bitmap & srcToTgtMap, DynamicElementStorageType storageType)
    : type_(storageType)
{
    int_changeDimensionality(other.variant(), value_, other.activeBits(), activeBits_, srcToTgtMap, type_);
}

#define EQUAL_VISIT(T1, T2) boost::apply_visitor(internal::equal_visit<T1, T2>(lset, rset), variant(), rhs.variant())

bool Element::operator==(const Element & rhs) const
{
    Bitset lset, rset;
    std::size_t bits = create_minimal_bitset(activeBits(), rhs.activeBits(), lset, rset);

    std::size_t mask = (1 << bits) - 1;

    if(lset.to_ulong() == mask)
        if(rset.to_ulong() == mask)
            return EQUAL_VISIT(IdentityIndexMap, IdentityIndexMap);
        else
            return EQUAL_VISIT(IdentityIndexMap, SubsetIndexMap);
    else
        if(rset.to_ulong() == mask)
            return EQUAL_VISIT(SubsetIndexMap, IdentityIndexMap);
        else
            return EQUAL_VISIT(SubsetIndexMap, SubsetIndexMap);

}

bool Element::operator!=(const Element & rhs) const
{
    return ! operator ==(rhs);
}

void Element::reset()
{
    reset(variant(), type(), activeBits());
}

bool Element::isZero() const
{
    return boost::apply_visitor(internal::is_zero_visitor(), variant());
}

std::size_t Element::nonZeroCount() const
{
    return boost::apply_visitor(internal::count_non_zero_visit(), variant());
}

void Element::reset(variant_type & value, DynamicElementStorageType type, const Bitset & activeBits)
{
    switch(type)
    {
    case SparseStorage:
        value = SparseRepresentation();
        initialize(boost::get<Sparse>(value));
        break;

    case DenseStorage:
        value = DenseRepresentation();
        initialize(boost::get<Dense>(value), activeBits.count());
        break;

    }
}

DynamicElementStorageType Element::type() const
{
    return type_;
}

void Element::changeType(DynamicElementStorageType type)
{
    // is it something trivial?
    if(type == type_)
        return;

    // initialise a temporary
    variant_type res;
    reset(res, type, activeBits());

    // copy to it
    boost::apply_visitor(internal::copy_visit(), value_, res);

    // and swap it into place
    swap(value_, res);
    type_ = type;
}


#define AGGREGATE_VISIT(T1, T2) boost::apply_visitor(internal::aggregate_bits_visit<T1, T2>(srcBitset, tgtBitset, mask), src, tgt)

void Element::int_aggregateBits(const variant_type & src, variant_type & tgt, const Bitset & srcBitset, Bitset & tgtBitset, const Bitset & bitsToKeep, DynamicElementStorageType storageType) const
{
    // initialize the target element
    tgtBitset = srcBitset & bitsToKeep;
    reset(tgt, storageType, tgtBitset);

    // get the mask
    Z2k::storage_type mask = bitsToKeep.to_ulong();

    // and the use the aggregate bits vistor
    if(is_contiguous(srcBitset))
        if(is_contiguous(tgtBitset))
            AGGREGATE_VISIT(IdentityIndexMap, IdentityIndexMap);
        else
            AGGREGATE_VISIT(IdentityIndexMap, SubsetIndexMap);
    else
        if(is_contiguous(tgtBitset))
            AGGREGATE_VISIT(SubsetIndexMap, IdentityIndexMap);
        else
            AGGREGATE_VISIT(SubsetIndexMap, SubsetIndexMap);
}

void Element::aggregateBits(const Bitset & bitsToKeep)
{
    aggregateBits(bitsToKeep, type());
}


void Element::aggregateBits(const Bitset & bitsToKeep, DynamicElementStorageType storageType)
{
    variant_type other;
    int_aggregateBits(variant(), other, Bitset(activeBits()), activeBits_, bitsToKeep, storageType);

    swap(other, value_);
    type_ = storageType;
}

#define CHANGE_DIM_VISIT(T1, T2) boost::apply_visitor(internal::change_dimensionality_visit<T1, T2>(srcBitset, tgtBitset, srcToTgtMap), src, tgt)

void Element::int_changeDimensionality(const variant_type & src, variant_type & tgt, const Bitset & srcBitset, Bitset & tgtBitset, const Bitmap & srcToTgtMap, DynamicElementStorageType storageType) const
{
    tgtBitset = Bitset(0);

    // set the active bits
    for(Bitmap::const_iterator it = srcToTgtMap.begin(); it != srcToTgtMap.end(); ++it)
        tgtBitset[it->second] = true;

    // construct the type
    reset(tgt, storageType, tgtBitset);

    // and use the change dimensionality visitor
    if(is_contiguous(srcBitset))
        if(is_contiguous(tgtBitset))
            CHANGE_DIM_VISIT(IdentityIndexMap, IdentityIndexMap);
        else
            CHANGE_DIM_VISIT(IdentityIndexMap, SubsetIndexMap);
    else
        if(is_contiguous(tgtBitset))
            CHANGE_DIM_VISIT(SubsetIndexMap, IdentityIndexMap);
        else
            CHANGE_DIM_VISIT(SubsetIndexMap, SubsetIndexMap);
}

void Element::changeDimensionality(const Bitmap & srcToTgtMap, DynamicElementStorageType storageType)
{
    variant_type other;
    int_changeDimensionality(variant(), other, Bitset(activeBits()), activeBits_, srcToTgtMap, storageType);

    swap(other, value_);
    type_ = storageType;
}

void Element::changeDimensionality(const Bitmap & srcToTgtMap)
{
    changeDimensionality(srcToTgtMap, type());
}




Element::variant_type & Element::variant()
{
    return value_;
}

const Element::variant_type & Element::variant() const
{
    return value_;
}

const Bitset & Element::activeBits() const
{
    return activeBits_;
}

bool Element::valueInActiveBits(const Z2k & value) const
{
    return (value.getValue() & activeBits().to_ulong()) == value.getValue();
}

void Element::setCoefficient(const Z2k & value, const GaloisField & coefficient)
{
    assert(valueInActiveBits(value));
    boost::apply_visitor(internal::set_coefficient_visit(value, coefficient, activeBits()), variant());
}

GaloisField Element::coefficient(const Z2k & value) const
{
    if(!valueInActiveBits(value))
        return GaloisField::zero;

    return boost::apply_visitor(internal::get_coefficient_visit(value, activeBits()), variant());
}

void swap(Element & el1, Element & el2)
{
    using std::swap;

    swap(el1.value_, el2.value_);
    swap(el1.type_, el2.type_);
    swap(el1.activeBits_, el2.activeBits_);
}

std::ostream & operator<<(std::ostream & stream, const Element & element)
{
    boost::apply_visitor(internal::ostream_visit<SubsetIndexMap>(stream, element.activeBits()), element.variant());
    return stream;
}

} // namespace ext
} // namespace gf2Algebra

