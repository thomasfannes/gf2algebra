#include "dynamicAlgebra.hpp"
#include "dynamicVisitors.hpp"

namespace gf2Algebra {
namespace internal {

DynamicAlgebra::DynamicAlgebra(double cValue, std::size_t nValue)
    : c(cValue),
      n(nValue)
{
}

void DynamicAlgebra::add(const DynamicElementImpl & lhs, const DynamicElementImpl & rhs, DynamicElementImpl & tgt) const
{
    assert(lhs.k() == rhs.k());

    DynamicElementImpl::Bitset joinedSet = lhs.activeBits() | rhs.activeBits();
    unsigned char k = lhs.k();


    if(lhs.type() == SparseStorage && rhs.type() == SparseStorage)
        // sparse on sparse yields sparse, otherwise use dense
        tgt = DynamicElementImpl(k, joinedSet, SparseRepresentation);
    else if(joinedSet.count() == k)
        // we use the full k bits, so dense
        tgt = DynamicElementImpl(k, joinedSet, DenseStorage);
    else
        // a semi-dense representation
        tgt = DynamicElementImpl(k, joinedSet, SemiDenseStorage);

    // perform the addition
    boost::apply_visitor(add_visit(), lhs.variant(), rhs.variant(), tgt.variant());

    // check for element changing
    updateRepresentation(tgt);

}

void DynamicAlgebra::updateRepresentation(DynamicElementImpl & element) const
{
    static double sqrt2 = 1.414;

    std::size_t noBitsNeeded = element.activeBits().count();
    std::size_t noNonZeroCoeff = boost::apply_visitor(count_nonzero_visit(), element);

    double cutoff = c * (1 << (noBitsNeeded/2)) * (noBitsNeeded & 1 ? sqrt2 : 1);

    // go for a dense representation
    if(noNonZeroCoeff > cutoff)
    {
        if(noBitsNeeded == element.k())
            element.changeType(DenseStorage);
        else
            element.changeType(SemiDenseStorage);
    }
    else
        element.changeType(SparseRepresentation);

}

void DynamicAlgebra::addAssign(DynamicElementImpl & lhs, const DynamicElementImpl & rhs) const
{
    assert(lhs.k() == rhs.k() && lhs.activeBits() == rhs.activeBits());
    if(lhs.type() == SparseStorage && rhs.type() != SparseStorage)
    {
        if(lhs.activeBits().count() == lhs.k())
            lhs.changeType(DenseRepresentation);
        else
            lhs.changeType(SemiDenseStorage);
    }

    boost::apply_visitor(addd_visit(), lhs.variant(), rhs.variant());

}

void DynamicAlgebra::multiply(const DynamicElementImpl & lhs, const DynamicElementImpl & rhs, DynamicElementImpl & tgt) const
{
}

void DynamicAlgebra::initializeSparse(unsigned char k, const DynamicElementImpl::Bitset & activeBits, DynamicElementImpl::variant_type & variant) const
{
    variant = D
    initialize();
}

void DynamicAlgebra::initializeDense(unsigned char k, const DynamicElementImpl::Bitset & activeBits, DynamicElementImpl::variant_type & variant) const
{
}

} // namespace internal
} // namespace gf2Algebra

