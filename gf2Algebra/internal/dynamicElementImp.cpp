#include "dynamicElementImp.hpp"

#include "dynamicVisitors.hpp"

namespace gf2Algebra {
namespace internal {
namespace visitor {



} // visitor namespace


DynamicElementImpl::DynamicElementImpl()
    : value_(SparseRepresentation()),
      type_(SparseStorage),
      k_(0)

{
    reset();
}

DynamicElementImpl::DynamicElementImpl(unsigned char k, const Bitset & activeBits, DynamicElementStorageType type)
    : type_(type),
      activeBits_(activeBits),
      k_(k)
{
    reset(type_);
}




DynamicElementImpl::DynamicElementImpl(const DynamicElementImpl & other, DynamicElementStorageType storageType)
    : type_(storageType),
      activeBits_(other.activeBits_),
      k_(other.k_)

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
    boost::apply_visitor(copy_visit(), other.value_, value_);
}

void DynamicElementImpl::reset()
{
    reset(variant(), type(), activeBits(), k());
}

void DynamicElementImpl::reset(DynamicElementStorageType type)
{
    type_ = type;
    reset();
}

void DynamicElementImpl::reset(variant_type & value, DynamicElementStorageType type, const Bitset & activeBits, unsigned char k)
{
    switch(type)
    {
    case SparseStorage:
        value = SparseRepresentation();
        initialize(boost::get<Sparse>(value), k);

    case SemiDenseStorage:
        value = SemiDense(DenseRepresentation(), SubsetIndexMap(k, activeBits));
        initialize(boost::get<SemiDense>(value).first, activeBits.count());

    case DenseStorage:
        value = Dense();
        initialize(boost::get<Dense>(value).first, k);
    }
}

DynamicElementStorageType DynamicElementImpl::type() const
{
    return type_;
}

void DynamicElementImpl::changeType(DynamicElementStorageType type)
{
    // is it something trivial?
    if(type == type_)
        return;

    // initialise a temporary
    variant_type res;
    reset(res, type, activeBits(), k());

    // copy to it
    boost::apply_visitor(copy_visit(), value_, res);

    // and swap it into place
    swap(value_, res);
}

DynamicElementImpl::variant_type & DynamicElementImpl::variant()
{
    return value_;
}

const DynamicElementImpl::variant_type & DynamicElementImpl::variant() const
{
    return value_;
}

const DynamicElementImpl::Bitset & DynamicElementImpl::activeBits() const
{
    return activeBits_;
}

unsigned char DynamicElementImpl::k() const
{
    return k_;
}

void swap(DynamicElementImpl & el1, DynamicElementImpl & el2)
{
    using std::swap;

    swap(el1.value_, el2.value_);
    swap(el1.type_, el2.type_);
    swap(el1.activeBits_, el2.activeBits_);
}

} // namespace internal
} // namespace gf2Algebra

