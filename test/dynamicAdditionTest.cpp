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
static const std::size_t MAX_NO_BITS = 10;

void testAdditionSameBitset(std::size_t noBits, std::size_t noElements, DynamicElementStorageType lhsStorage, DynamicElementStorageType rhsStorage)
{
    std::size_t k2 = (1 << noBits);

    Bitset activeBits = k2 - 1;

    Element lhs(activeBits, lhsStorage);
    Element rhs(activeBits, rhsStorage);

    initializeElement(lhs, activeBits, noElements);
    initializeElement(rhs, activeBits, noElements);

    Element sum;
    algebra.add(lhs, rhs, sum);


    for(std::size_t j = 0; j < k2; ++j)
    {
        Z2k value(j);
        BOOST_CHECK_EQUAL(sum.coefficient(value), lhs.coefficient(value) + rhs.coefficient(value));
    }
}

void testAdditionDifferentBitset(std::size_t noBits, std::size_t noElements, DynamicElementStorageType lhsStorage, DynamicElementStorageType rhsStorage)
{
    Bitset lhsBitset, rhsBitset;
    for(std::size_t i = 0; i < noBits; ++i)
    {
        lhsBitset[i] = (std::rand()%2 == 0);
        rhsBitset[i] = (std::rand()%2 == 0);
    }

    std::size_t k2 = (1 << noBits);

    Element lhs(lhsBitset, lhsStorage);
    Element rhs(rhsBitset, rhsStorage);

    initializeElement(lhs, lhsBitset, noElements);
    initializeElement(rhs, rhsBitset, noElements);

    Element sum;
    algebra.add(lhs, rhs, sum);

    BOOST_CHECK_EQUAL(sum.activeBits(), lhsBitset | rhsBitset);


    for(std::size_t j = 0; j < k2; ++j)
    {
        Z2k value(j);
        BOOST_CHECK_EQUAL(sum.coefficient(value), lhs.coefficient(value) + rhs.coefficient(value));
    }
}

void testAdditionToZero(std::size_t noBits, std::size_t noElements, DynamicElementStorageType lhsStorage, DynamicElementStorageType rhsStorage)
{
    std::size_t k2 = (1 << noBits);
    Bitset activeBits = k2 - 1;

    Element lhs(activeBits, lhsStorage);
    Element rhs(activeBits, rhsStorage);

    initializeElement(lhs, activeBits, noElements);
    rhs = lhs;

    Element result;
    algebra.add(lhs , rhs, result);
    BOOST_CHECK_EQUAL(result.isZero(), true);
    BOOST_CHECK_EQUAL(result.nonZeroCount(), 0);
    BOOST_CHECK_EQUAL(result.activeBits(), activeBits);
}

void testAdditionAssignSameBitset(std::size_t noBits, std::size_t noElements, DynamicElementStorageType lhsStorage, DynamicElementStorageType rhsStorage)
{
    std::size_t k2 = (1 << noBits);

    Bitset activeBits = k2 - 1;

    Element lhs(activeBits, lhsStorage);
    Element rhs(activeBits, rhsStorage);

    initializeElement(lhs, activeBits, noElements);
    initializeElement(rhs, activeBits, noElements);

    Element sum;
    algebra.add(lhs, rhs, sum);

    algebra.addAssign(lhs, rhs);

    BOOST_CHECK_EQUAL(lhs, sum);

}


void testAdditionAssignDifferentBitset(std::size_t noBits, std::size_t noElements, DynamicElementStorageType lhsStorage, DynamicElementStorageType rhsStorage)
{
    Bitset lhsActiveBits, rhsActiveBits;
    for(std::size_t i = 0; i < noBits; ++i)
    {
        rhsActiveBits[i] = (std::rand() % 2 == 0);
        lhsActiveBits[i] = rhsActiveBits[i] || (std::rand()%2 == 0);
    }


    Element lhs(lhsActiveBits, lhsStorage);
    Element rhs(rhsActiveBits, rhsStorage);

    initializeElement(lhs, lhsActiveBits, noElements);
    initializeElement(rhs, rhsActiveBits, noElements);

    Element sum;
    algebra.add(lhs, rhs, sum);

    algebra.addAssign(lhs, rhs);

    BOOST_CHECK_EQUAL(lhs, sum);

}


BOOST_AUTO_TEST_CASE( general_addition_test )
{
    for(std::size_t i = 0; i < NO_OF_RUNS; ++i)
    {
        std::size_t noBits = (rand() % (MAX_NO_BITS-3)) + 3;
        std::size_t noElements = rand() % (1 << noBits);

        testAdditionDifferentBitset(noBits, noElements, SparseStorage, SparseStorage);
        testAdditionDifferentBitset(noBits, noElements, SparseStorage, DenseStorage);
        testAdditionDifferentBitset(noBits, noElements, DenseStorage, SparseStorage);
        testAdditionDifferentBitset(noBits, noElements, DenseStorage, DenseStorage);
    }
}

BOOST_AUTO_TEST_CASE( same_bitset_addition_test )
{
    for(std::size_t i = 0; i < NO_OF_RUNS; ++i)
    {
        std::size_t noBits = (rand() % (MAX_NO_BITS-3)) + 3;
        std::size_t noElements = rand() % (1 << noBits);

        testAdditionSameBitset(noBits, noElements, SparseStorage, SparseStorage);
        testAdditionSameBitset(noBits, noElements, SparseStorage, DenseStorage);
        testAdditionSameBitset(noBits, noElements, DenseStorage, SparseStorage);
        testAdditionSameBitset(noBits, noElements, DenseStorage, DenseStorage);
    }
}

BOOST_AUTO_TEST_CASE( general_addition_zero_test )
{
    for(std::size_t i = 0; i < NO_OF_RUNS; ++i)
    {
        std::size_t noBits = (rand() % (MAX_NO_BITS-3)) + 3;
        std::size_t noElements = rand() % (1 << noBits);

        testAdditionToZero(noBits, noElements, SparseStorage, SparseStorage);
        testAdditionToZero(noBits, noElements, SparseStorage, DenseStorage);
        testAdditionToZero(noBits, noElements, DenseStorage, SparseStorage);
        testAdditionToZero(noBits, noElements, DenseStorage, DenseStorage);
    }
}

BOOST_AUTO_TEST_CASE( same_bitset_addition_assign_test )
{
    for(std::size_t i = 0; i < NO_OF_RUNS; ++i)
    {
        std::size_t noBits = (rand() % (MAX_NO_BITS-3)) + 3;
        std::size_t noElements = rand() % (1 << noBits);

        testAdditionAssignSameBitset(noBits, noElements, SparseStorage, SparseStorage);
        testAdditionAssignSameBitset(noBits, noElements, SparseStorage, DenseStorage);
        testAdditionAssignSameBitset(noBits, noElements, DenseStorage, SparseStorage);
        testAdditionAssignSameBitset(noBits, noElements, DenseStorage, DenseStorage);
    }
}


BOOST_AUTO_TEST_CASE( different_bitset_addition_assign_test )
{
    for(std::size_t i = 0; i < NO_OF_RUNS; ++i)
    {
        std::size_t noBits = (rand() % (MAX_NO_BITS-3)) + 3;
        std::size_t noElements = rand() % (1 << noBits);

        testAdditionAssignDifferentBitset(noBits, noElements, SparseStorage, SparseStorage);
        testAdditionAssignDifferentBitset(noBits, noElements, SparseStorage, DenseStorage);
        testAdditionAssignDifferentBitset(noBits, noElements, DenseStorage, SparseStorage);
        testAdditionAssignDifferentBitset(noBits, noElements, DenseStorage, DenseStorage);
    }
}

