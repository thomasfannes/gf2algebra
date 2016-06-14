#include "sparseElement.hpp"
#include <cassert>

namespace gf2Algebra {
namespace config {

SparseCoefficient::SparseCoefficient()
    : coefficient(), value(0)
{
}

SparseCoefficient::SparseCoefficient(const field_type & coeff, const group_type & val)
    : coefficient(coeff), value(val)
{
}

SparseCoefficient & SparseCoefficient::operator+=(const SparseCoefficient & rhs)
{
    assert(this->value == rhs.value);
    this->coefficient += rhs.coefficient;

    return *this;
}

SparseCoefficient SparseCoefficient::operator+(const SparseCoefficient & rhs) const
{
    assert(this->value == rhs.value);
    return SparseCoefficient(this->coefficient + rhs.coefficient, this->value);
}

SparseCoefficient SparseCoefficient::operator*(const SparseCoefficient & rhs) const
{
    return SparseCoefficient(this->coefficient * rhs.coefficient, this->value * rhs.value);
}

bool SparseCoefficient::operator<(const SparseCoefficient & rhs) const
{
    return this->value < rhs.value;
}

bool SparseCoefficient::operator==(const SparseCoefficient & rhs) const
{
    return this->value == rhs.value && this->coefficient == rhs.coefficient;
}

bool SparseCoefficient::operator!=(const SparseCoefficient & rhs) const
{
    return this->value != rhs.value || this->coefficient != rhs.coefficient;
}

bool SparseCoefficient::isZero() const
{
    return this->coefficient == field_type::zero;
}

void swap(SparseCoefficient & lhs, SparseCoefficient & rhs)
{
    using std::swap;

    swap(lhs.coefficient, rhs.coefficient);
    swap(lhs.value, rhs.value);
}


} // config namespace


SparseElement::SparseElement()
{
}


bool SparseElement::isZero() const
{
    assert(isValid());

    return this->empty();
}

bool SparseElement::isValid() const
{
    // A sparse element is valid if it is sorted and does not contain any zero coefficients
    for(std::size_t pos = 1; pos < this->size(); ++pos)
        if(!(at(pos-1) < at(pos)))
            return false;

    for(const_iterator it = begin(); it != end(); ++it)
        if(it->isZero())
            return false;

    return true;
}

std::size_t SparseElement::countNonZero()
{
    assert(isValid());

    return this->size();
}


} // gf2Algebra namespace
