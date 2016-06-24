#define BOOST_TEST_MODULE TransformTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <gf2Algebra/ext/element.hpp>
#include <gf2Algebra/ext/algebra.hpp>
#include "util.hpp"

using namespace gf2Algebra;
using namespace gf2Algebra::ext;

Algebra algebra;

static const std::size_t NO_OF_RUNS = 100;
static const std::size_t MAX_NO_BITS = 7;

void checkMultiplicationResult(const Element & lhs, const Element & rhs, const Element & tgt)
{
    // find the largest bit
    std::size_t largestBit = 0;
    while( (tgt.activeBits().to_ulong() >> largestBit) != 0)
        ++largestBit;

    std::size_t k2 = (1 << largestBit);

    for(std::size_t i = 0; i < k2; ++i)
    {
        Z2k value(i);
        GaloisField coeff;

        for(std::size_t j = 0; j < k2; ++j)
        {
            Z2k vl(j);
            Z2k vr = value * vl;

            coeff += (lhs.coefficient(vl) * rhs.coefficient(vr));
        }

        BOOST_CHECK_EQUAL(coeff, tgt.coefficient(value));
    }
}

void testMultiplicationSameBitset(std::size_t noBits, std::size_t noElements, DynamicElementStorageType lhsStorage, DynamicElementStorageType rhsStorage)
{
    std::size_t k2 = (1 << noBits);

    Bitset activeBits = k2 - 1;

    Element lhs(activeBits, lhsStorage);
    Element rhs(activeBits, rhsStorage);

    initializeElement(lhs, activeBits, noElements);
    initializeElement(rhs, activeBits, noElements);

    Element prod;
    algebra.multiply(lhs, rhs, prod);

    checkMultiplicationResult(lhs, rhs, prod);
}

void testMultiplicationDifferentBitset(std::size_t noBits, std::size_t noElements, DynamicElementStorageType lhsStorage, DynamicElementStorageType rhsStorage)
{
    Bitset lr, nr;

    for(std::size_t i = 0; i < noBits; ++i)
    {
        lr[i] = (std::rand() % 2 == 0);
        nr[i] = (std::rand() % 2 == 0);
    }

    Element lhs(lr, lhsStorage);
    Element rhs(nr, rhsStorage);

    initializeElement(lhs, lr, noElements);
    initializeElement(rhs, nr, noElements);

    Element prod;
    algebra.multiply(lhs, rhs, prod);

    checkMultiplicationResult(lhs, rhs, prod);
}

void testMultiplicationSquares(std::size_t noBits, DynamicElementStorageType lhsStorage, DynamicElementStorageType rhsStorage)
{
    Bitset activeBits;
    for(std::size_t i = 0; i < noBits; ++i)
        activeBits[std::rand() & MAX_K_VALUE] = true;

    Element lhs(activeBits, lhsStorage);

    // get a non-zero value
    Z2k value;
    while(value.getValue() == 0)
        value = Z2k( rand() & activeBits.to_ulong() );

    // get a coeff
    GaloisField coeff( rand() & 255 );

    lhs.setCoefficient(value, coeff);
    lhs.setCoefficient(Z2k(), coeff);


    Element rhs(lhs, rhsStorage);

    Element prod;
    algebra.multiply(lhs, rhs, prod);

    BOOST_CHECK_EQUAL(prod.isZero(), true);
}

BOOST_AUTO_TEST_CASE( squares_multiplication_test )
{
    for(std::size_t i = 0; i < NO_OF_RUNS; ++i)
    {
        std::size_t noBits = (rand() % (MAX_NO_BITS-3)) + 3;

        testMultiplicationSquares(noBits, SparseStorage, SparseStorage);
        testMultiplicationSquares(noBits, SparseStorage, DenseStorage);
        testMultiplicationSquares(noBits, DenseStorage, SparseStorage);
        testMultiplicationSquares(noBits, DenseStorage, DenseStorage);
    }
}

BOOST_AUTO_TEST_CASE( different_bitset_multiplication_test )
{
    for(std::size_t i = 0; i < NO_OF_RUNS; ++i)
    {
        std::size_t noBits = (rand() % (MAX_NO_BITS-3)) + 3;
        std::size_t noElements = rand() % (1 << noBits);

        testMultiplicationDifferentBitset(noBits, noElements, SparseStorage, SparseStorage);
        testMultiplicationDifferentBitset(noBits, noElements, SparseStorage, DenseStorage);
        testMultiplicationDifferentBitset(noBits, noElements, DenseStorage, SparseStorage);
        testMultiplicationDifferentBitset(noBits, noElements, DenseStorage, DenseStorage);
    }
}

BOOST_AUTO_TEST_CASE( same_bitset_multiplication_test )
{
    for(std::size_t i = 0; i < NO_OF_RUNS; ++i)
    {
        std::size_t noBits = (rand() % (MAX_NO_BITS-3)) + 3;
        std::size_t noElements = rand() % (1 << noBits);

        testMultiplicationSameBitset(noBits, noElements, SparseStorage, SparseStorage);
        testMultiplicationSameBitset(noBits, noElements, SparseStorage, DenseStorage);
        testMultiplicationSameBitset(noBits, noElements, DenseStorage, SparseStorage);
        testMultiplicationSameBitset(noBits, noElements, DenseStorage, DenseStorage);
    }
}
