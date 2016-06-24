#define BOOST_TEST_MODULE TransformTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <gf2Algebra/ext/element.hpp>
#include "util.hpp"

using namespace gf2Algebra;
using namespace gf2Algebra::ext;

BOOST_AUTO_TEST_CASE( Sparse_init_test )
{
    Element el1;

    BOOST_CHECK_EQUAL(el1.type(), SparseStorage);
    BOOST_CHECK_EQUAL(el1.activeBits().count(), 0);
    BOOST_CHECK_EQUAL(boost::get<SparseRepresentation>(el1.variant()).size(), 0);
    BOOST_CHECK_EQUAL(el1.isZero(), true);
    BOOST_CHECK_EQUAL(el1.nonZeroCount(), 0);


    Element el2(Bitset(2), SparseStorage);

    BOOST_CHECK_EQUAL(el2.type(), SparseStorage);
    BOOST_CHECK_EQUAL(el2.activeBits().count(), 1);
    BOOST_CHECK_EQUAL(boost::get<SparseRepresentation>(el2.variant()).size(), 0);
    BOOST_CHECK_EQUAL(el2.isZero(), true);
    BOOST_CHECK_EQUAL(el1.nonZeroCount(), 0);


    Element el3(Bitset(7), SparseStorage);

    BOOST_CHECK_EQUAL(el3.type(), SparseStorage);
    BOOST_CHECK_EQUAL(el3.activeBits().count(), 3);
    BOOST_CHECK_EQUAL(boost::get<SparseRepresentation>(el3.variant()).size(), 0);
    BOOST_CHECK_EQUAL(el3.isZero(), true);
    BOOST_CHECK_EQUAL(el1.nonZeroCount(), 0);
}


BOOST_AUTO_TEST_CASE( Dense_init_test )
{
    Element el1(Bitset(0), DenseStorage);

    BOOST_CHECK_EQUAL(el1.type(), DenseStorage);
    BOOST_CHECK_EQUAL(el1.activeBits().count(), 0);
    BOOST_CHECK_EQUAL(boost::get<DenseRepresentation>(el1.variant()).size(), 1);
    BOOST_CHECK_EQUAL(el1.isZero(), true);
    BOOST_CHECK_EQUAL(el1.nonZeroCount(), 0);


    Element el2(Bitset(2), DenseStorage);

    BOOST_CHECK_EQUAL(el2.type(), DenseStorage);
    BOOST_CHECK_EQUAL(el2.activeBits().count(), 1);
    BOOST_CHECK_EQUAL(boost::get<DenseRepresentation>(el2.variant()).size(), 2);
    BOOST_CHECK_EQUAL(el2.isZero(), true);
    BOOST_CHECK_EQUAL(el1.nonZeroCount(), 0);


    Element el3(Bitset(7), DenseStorage);

    BOOST_CHECK_EQUAL(el3.type(), DenseStorage);
    BOOST_CHECK_EQUAL(el3.activeBits().count(), 3);
    BOOST_CHECK_EQUAL(boost::get<DenseRepresentation>(el3.variant()).size(), 8);
    BOOST_CHECK_EQUAL(el3.isZero(), true);
    BOOST_CHECK_EQUAL(el1.nonZeroCount(), 0);
}


BOOST_AUTO_TEST_CASE( Sparse_simple_test )
{
    Element el1(Bitset((1<<5)-1), SparseStorage);

    el1.setCoefficient(Z2k(0), GaloisField(12));
    BOOST_CHECK_EQUAL(el1.type(), SparseStorage);
    BOOST_CHECK_EQUAL(el1.isZero(), false);
    BOOST_CHECK_EQUAL(el1.nonZeroCount(), 1);
    BOOST_CHECK_EQUAL(boost::get<SparseRepresentation>(el1.variant()).size(), 1);

    Element el2(el1);
    BOOST_CHECK_EQUAL(el2.type(), SparseStorage);
    BOOST_CHECK_EQUAL(el2.isZero(), 0);
    BOOST_CHECK_EQUAL(el2.nonZeroCount(), 1);
    BOOST_CHECK_EQUAL(boost::get<SparseRepresentation>(el2.variant()).size(), 1);
}

BOOST_AUTO_TEST_CASE( Dense_simple_test )
{
    Element el1(Bitset((1<<5)-1), DenseStorage);

    el1.setCoefficient(Z2k(0), GaloisField(12));
    BOOST_CHECK_EQUAL(el1.type(), DenseStorage);
    BOOST_CHECK_EQUAL(el1.isZero(), false);
    BOOST_CHECK_EQUAL(el1.nonZeroCount(), 1);
    BOOST_CHECK_EQUAL(boost::get<DenseRepresentation>(el1.variant()).size(), 32);

    Element el2(el1);
    BOOST_CHECK_EQUAL(el2.type(), DenseStorage);
    BOOST_CHECK_EQUAL(el2.isZero(), 0);
    BOOST_CHECK_EQUAL(el2.nonZeroCount(), 1);
    BOOST_CHECK_EQUAL(boost::get<DenseRepresentation>(el2.variant()).size(), 32);
}

BOOST_AUTO_TEST_CASE( equality_test )
{
    Element el1(Bitset( (1<<8) - 1), SparseStorage);
    initializeElement(el1, Bitset( (1<<8) - 1), 100);
    BOOST_CHECK(el1.nonZeroCount() > 0);
    BOOST_CHECK(el1.nonZeroCount() < 100);

    Element el2(el1, DenseStorage);
    BOOST_CHECK(el2.nonZeroCount() > 0);
    BOOST_CHECK(el2.nonZeroCount() < 100);
    BOOST_CHECK_EQUAL(el1, el2);

    el2.changeType(SparseStorage);
    BOOST_CHECK_EQUAL(el2.type(), SparseStorage);
    BOOST_CHECK_EQUAL(el2.nonZeroCount(), el1.nonZeroCount());
    BOOST_CHECK_EQUAL(el1, el2);

    el2.changeType(DenseStorage);
    BOOST_CHECK_EQUAL(el2.type(), DenseStorage);
    BOOST_CHECK_EQUAL(el2.nonZeroCount(), el1.nonZeroCount());
    BOOST_CHECK_EQUAL(el1, el2);
}
