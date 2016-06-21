#ifndef GF2ALGEBRA_INTERNAL_DYNAMICELEMENTIMP_HPP
#define GF2ALGEBRA_INTERNAL_DYNAMICELEMENTIMP_HPP

#include "../representation.hpp"
#include "../identityIndexMap.hpp"
#include "../subsetIndexMap.hpp"
#include "../dynamicElementStorageType.hpp"


#include <boost/variant.hpp>
#include <bitset>

namespace gf2Algebra {
namespace internal {

class DynamicElementImpl
{
    typedef SparseRepresentation Sparse;
    typedef std::pair<DenseRepresentation, SubsetIndexMap> SemiDense;
    typedef std::pair<DenseRepresentation, IdentityIndexMap> Dense;

public:
    typedef boost::variant<Sparse, SemiDense, Dense> variant_type;
    typedef std::bitset<MAX_K_VALUE> Bitset;


    DynamicElementImpl();
    DynamicElementImpl(unsigned char k, const Bitset & activeBits, DynamicElementStorageType type);
    DynamicElementImpl(const DynamicElementImpl & other, DynamicElementStorageType storageType);

    DynamicElementStorageType type() const;
    void changeType(DynamicElementStorageType type);



private:
    void initValue(variant_type & value, DynamicElementStorageType type) const;
    friend void swap(DynamicElementImpl & el1, DynamicElementImpl & el2);

    variant_type value_;
    DynamicElementStorageType type_;
    Bitset activeBits_;
    unsigned char k_;
};

} // namespace internal
} // namespace gf2Algebra

#endif // GF2ALGEBRA_INTERNAL_DYNAMICELEMENTIMP_HPP
