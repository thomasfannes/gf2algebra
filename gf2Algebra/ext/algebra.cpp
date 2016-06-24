
#include "algebra.hpp"

#include "internal/dynamicVisitors.hpp"
#include <boost/variant/multivisitors.hpp>

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


std::size_t create_minimal_bitsets(
        const Bitset & lhsActiveBits,
        const Bitset & rhsActiveBits,
        const Bitset & requiredMask,
        Bitset & minLhsSet,
        Bitset & minRhsSet,
        Bitset & minJoinSet,
        Z2k::storage_type & minimalMask)
{
    minimalMask = 0;
    std::size_t curBit = 0;

    for(std::size_t i = 0; i < MAX_K_VALUE; ++i)
    {
        // is bit i active?
        if(lhsActiveBits[i] || rhsActiveBits[i])
        {
            // yes, so map it to bit curBit
            minLhsSet.set(curBit, lhsActiveBits[i]);
            minRhsSet.set(curBit, rhsActiveBits[i]);

            // do we need this bit in the join?
            if(requiredMask[i])
            {
                // yes we do, so add it to the interpretation
                minJoinSet.set(curBit);

                // and to mask
                minimalMask |= (1 << curBit);
            }

            // increase the current bit
            ++curBit;
        }
    }

    return curBit;
}


} // anonymous namespace


Algebra::Algebra(double cValue, double nValue)
    : c(cValue),
      n(nValue)
{
}

#define ADD_VISIT(T1, T2) boost::apply_visitor(internal::add_visit<T1, T2>(nl, nr), lhs.variant(), rhs.variant(), tgt.variant())

void Algebra::add(const element_type & lhs, const element_type & rhs, element_type & tgt) const
{
    // create the tgt element
    Bitset tgtActiveBits = lhs.activeBits() | rhs.activeBits();
    tgt = Element(tgtActiveBits, static_cast<DynamicElementStorageType>(lhs.type() * rhs.type()) );

    // create the interpretation bitset
    Bitset nl, nr;
    create_minimal_bitset(lhs.activeBits(), rhs.activeBits(), nl, nr);

    // call the add visitor with the right index map
    if(is_contiguous(nl))
    {
        if(is_contiguous(nr))
            ADD_VISIT(IdentityIndexMap, IdentityIndexMap);
        else
            ADD_VISIT(IdentityIndexMap, SubsetIndexMap);
    }
    else
    {
        if(is_contiguous(nr))
            ADD_VISIT(SubsetIndexMap, IdentityIndexMap);
        else
            ADD_VISIT(SubsetIndexMap, SubsetIndexMap);
    }

    // and check whether we need to change the representation
    updateRepresentation(tgt);
}

#define ADD_ASSIGN_VISIT(T) boost::apply_visitor(internal::add_assign_visit<T>(nr), lhs.variant(), rhs.variant())

void Algebra::addAssign(element_type & lhs, const element_type & rhs) const
{
    assert( (lhs.activeBits() | rhs.activeBits()) == lhs.activeBits());

    Bitset nl, nr;
    create_minimal_bitset(lhs.activeBits(), rhs.activeBits(), nl, nr);

    // perform the addition
    if(is_contiguous(nr))
        ADD_ASSIGN_VISIT(IdentityIndexMap);
    else
        ADD_ASSIGN_VISIT(SubsetIndexMap);

    // and check whether we need to change the representation
    updateRepresentation(lhs);

}

void Algebra::multiply(const element_type & lhs, const element_type & rhs, element_type & tgt) const
{
    multiply(lhs, rhs, tgt, lhs.activeBits() | rhs.activeBits());
}


template <typename IndexMap1, typename IndexMap2, typename IndexMap3>
void call_multiply(
        const Bitset & lhsBitset,
        const Bitset & rhsBitset,
        const Bitset & joinBitset,
        Z2k::storage_type mask,
        std::size_t k,
        const Element & lhs,
        const Element & rhs,
        Element & tgt,
        bool useFFT
        )
{
    // do we need a mask?
    bool needMask = (mask == (1<<k)-1);

    if(useFFT)
    {
        if(needMask)
            boost::apply_visitor(
                internal::multiply_fft_mask_visit<IndexMap1, IndexMap2, IndexMap3>(lhsBitset, rhsBitset, joinBitset, mask, k),
                lhs.variant(),
                rhs.variant(),
                tgt.variant() );
        else
            boost::apply_visitor(
                internal::multiply_fft_visit<IndexMap1, IndexMap2, IndexMap3>(lhsBitset, rhsBitset, joinBitset, k),
                lhs.variant(),
                rhs.variant(),
                tgt.variant() );
    }
    else
    {
        if(needMask)
            boost::apply_visitor(
                internal::multiply_quadratic_mask_visit<IndexMap1, IndexMap2, IndexMap3>(lhsBitset, rhsBitset, joinBitset, mask),
                lhs.variant(),
                rhs.variant(),
                tgt.variant() );
        else
            boost::apply_visitor(
                internal::multiply_quadratic_visit<IndexMap1, IndexMap2, IndexMap3>(lhsBitset, rhsBitset, joinBitset),
                lhs.variant(),
                rhs.variant(),
                tgt.variant() );
    }

}

#define MULTIPLY_VISIT(T1, T2, T3) call_multiply<T1, T2, T3>(minLhs, minRhs, minJoin, mask, k, lhs, rhs, tgt, use_fft)

void Algebra::multiply(const element_type & lhs, const element_type & rhs, element_type & tgt, Bitset tgtActiveBits) const
{
    // make sure we do not need bits which are not set by lhs or rhs
    tgtActiveBits &= (lhs.activeBits() | rhs.activeBits());
    tgt = Element(tgtActiveBits, static_cast<DynamicElementStorageType>(lhs.type() * rhs.type()) );

    Bitset minLhs, minRhs, minJoin;
    Z2k::storage_type mask;

    // find the minimal bitset configuration
    std::size_t k = create_minimal_bitsets(lhs.activeBits(), rhs.activeBits(), tgtActiveBits, minLhs, minRhs, minJoin, mask);

    bool use_fft = false;
    if(lhs.type() == DenseStorage && rhs.type() == DenseStorage)
        use_fft = useFFT(minLhs.count(), minRhs.count(), minJoin.count());

    if(is_contiguous(minLhs))
        if(is_contiguous(minRhs))
            if(is_contiguous(minJoin))
                MULTIPLY_VISIT(IdentityIndexMap, IdentityIndexMap, IdentityIndexMap);
            else
                MULTIPLY_VISIT(IdentityIndexMap, IdentityIndexMap, SubsetIndexMap);
        else
            if(is_contiguous(minJoin))
                MULTIPLY_VISIT(IdentityIndexMap, SubsetIndexMap, IdentityIndexMap);
            else
                MULTIPLY_VISIT(IdentityIndexMap, SubsetIndexMap, SubsetIndexMap);
    else
        if(is_contiguous(minRhs))
            if(is_contiguous(minJoin))
                MULTIPLY_VISIT(SubsetIndexMap, IdentityIndexMap, IdentityIndexMap);
            else
                MULTIPLY_VISIT(SubsetIndexMap, IdentityIndexMap, SubsetIndexMap);
        else
            if(is_contiguous(minJoin))
                MULTIPLY_VISIT(SubsetIndexMap, SubsetIndexMap, IdentityIndexMap);
            else
                MULTIPLY_VISIT(SubsetIndexMap, SubsetIndexMap, SubsetIndexMap);


    updateRepresentation(tgt);

}

DynamicElementStorageType Algebra::calculatePreferredRepresentationStorageType(const element_type & element) const
{
    std::size_t nonZeroCount = element.isZero();
    std::size_t k = element.activeBits().count();

    const static double sqrt2 = 1.414;

    if (nonZeroCount < ((1 << k/2) * c * (k%2 == 0 ? 1 : sqrt2)))
        return SparseStorage;
    else
        return DenseStorage;
}

void Algebra::updateRepresentation(element_type & element) const
{
    DynamicElementStorageType newType = calculatePreferredRepresentationStorageType(element);
    if(element.type() != newType)
        element.changeType(newType);
}

bool Algebra::useFFT(unsigned char leftK, unsigned char rightK, unsigned char joinK) const
{
    assert(joinK <= leftK + rightK);
    std::size_t lhs = (1 << (leftK + rightK - joinK));
    std::size_t rhs = n*joinK;

    return lhs >= rhs;
}


} // namespace ext
} // namespace gf2Algebra

