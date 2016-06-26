#ifndef GF2ALGEBRA_DYNAMICELEMENTSTORAGETYPE_HPP
#define GF2ALGEBRA_DYNAMICELEMENTSTORAGETYPE_HPP

namespace gf2Algebra {

/**
 * @brief The DynamicElementStorageType enum defines the storage type that is used
 *
 * DenseStorage implies many non-zero coefficients
 * SparseStorage implies many zero coefficients
 */
enum DynamicElementStorageType
{
    DenseStorage = 0,
    SparseStorage = 1
};

} // gf2Algebra namespace

#endif // GF2ALGEBRA_DYNAMICELEMENTSTORAGETYPE_HPP

