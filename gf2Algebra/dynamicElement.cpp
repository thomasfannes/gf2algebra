#include "dynamicElement.hpp"
#include "ext/element.hpp"
#include "ext/algebra.hpp"

namespace gf2Algebra {
namespace {

static const ext::Algebra & algebra()
{
    static ext::Algebra alg;
    return alg;
}

} //  namespace

struct DynamicElement::Impl
{
    Impl()
    {
    }

    Impl(const Bitset & activeBits, const DynamicElementStorageType & type)
        : element(activeBits, type)
    {
    }

    Impl(const ext::Element & rhs)
        : element(rhs)
    {
    }


    ext::Element element;
};

// constructor
DynamicElement::DynamicElement()
    : d_(new Impl)
{
}

DynamicElement::DynamicElement(const Bitset & activeBits, DynamicElementStorageType storage)
    : d_(new Impl(activeBits, storage))
{

}

DynamicElement::DynamicElement(const DynamicElement & element)
    : d_(element.d_)
{
}

// operators
DynamicElement & DynamicElement::operator=(const DynamicElement & rhs)
{
    d_ = rhs.d_;
    return *this;
}

DynamicElement & DynamicElement::operator+=(const DynamicElement & rhs)
{
    makeUniqueIfNecessary();
    algebra().addAssign(d_->element, rhs.d_->element);

    return *this;
}

DynamicElement DynamicElement::operator+(const DynamicElement & rhs) const
{
    DynamicElement result;
    algebra().add(d_->element, rhs.d_->element, result.d_->element);

    return result;
}

DynamicElement DynamicElement::operator*(const DynamicElement & rhs) const
{
    DynamicElement result;
    algebra().multiply(d_->element, rhs.d_->element, result.d_->element);

    return result;
}

DynamicElement DynamicElement::multiply(const DynamicElement & rhs, const Bitset & targetBits) const
{
    DynamicElement result;
    algebra().multiply(d_->element, rhs.d_->element, result.d_->element, targetBits);

    return result;
}

bool DynamicElement::operator==(const DynamicElement & rhs) const
{
    return d_ == rhs.d_ || d_->element == rhs.d_->element;
}

bool DynamicElement::operator!=(const DynamicElement & rhs) const
{
    return !operator ==(rhs);
}

// alteration methods
void DynamicElement::setCoefficient(const Z2k & value, const GaloisField & coefficient)
{
    makeUniqueIfNecessary();
    d_->element.setCoefficient(value, coefficient);
}

GaloisField DynamicElement::coefficient(const Z2k & value) const
{
    return d_->element.coefficient(value);
}

// information methods
bool DynamicElement::isZero() const
{
    return d_->element.isZero();
}
std::size_t DynamicElement::nonZeroCount() const
{
    return d_->element.nonZeroCount();
}

void DynamicElement::reset()
{
    makeUniqueIfNecessary();
    d_->element.reset();
}

DynamicElementStorageType DynamicElement::storageType() const
{
    return d_->element.type();
}

void DynamicElement::changeStorageType(DynamicElementStorageType newType)
{
    makeUniqueIfNecessary();
    d_->element.changeType(newType);
}


void DynamicElement::makeUniqueIfNecessary()
{
    if(d_.unique())
        return;

    d_ = boost::shared_ptr<Impl>(new Impl(d_->element));
}

void swap(DynamicElement & lhs, DynamicElement & rhs)
{
    using std::swap;

    swap(lhs.d_, rhs.d_);
}

std::ostream & operator<<(std::ostream & stream, const DynamicElement & element)
{
    stream << element.d_->element;
    return stream;
}

} // namespace gf2Algebra

