#define BOOST_TEST_MODULE OperationTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include <gf2Algebra/representation.hpp>
#include <gf2Algebra/operations/transform.hpp>
#include "util.hpp"


void performDenseToSparseTest(std::size_t sz, std::size_t noValues, std::size_t k)
{
    for(std::size_t i = 0; i < sz; ++i)
    {
        // init of the source
        std::pair<DenseRepresentation, IdentityIndexMap> src = generateRandom(k, noValues, DenseTag());

        // init of the target
        SparseRepresentation tgt;
        initialize(tgt, k);

        // copying
        makeSparse(src, tgt);

        // and checking
        BOOST_REQUIRE( checkEqual(make_value_coefficient_input_range(src), make_value_coefficient_input_range(tgt)) );
    }
}


void performSparseToDenseTest(std::size_t sz, std::size_t noValues, std::size_t k)
{
    for(std::size_t i = 0; i < sz; ++i)
    {
        // init of the source
        SparseRepresentation src = generateRandom(k, noValues, SparseTag());

        // init of the target
        std::pair<DenseRepresentation, IdentityIndexMap> tgt;
        initialize(tgt.first, k);

        // copying
        makeDense(src, tgt);

        // and checking
        BOOST_REQUIRE( checkEqual(make_value_coefficient_input_range(src), make_value_coefficient_input_range(tgt)) );
    }
}


BOOST_AUTO_TEST_CASE( Sparse_2_Dense )
{
    for(std::size_t k = 1; k < 5; ++k)
        for(int i = 1; i < (1<<k); ++i)
            performSparseToDenseTest(3, i, k);

}


BOOST_AUTO_TEST_CASE( Dense_2_Sparse )
{
    for(std::size_t k = 1; k < 5; ++k)
        for(int i = 1; i < (1<<k); ++i)
            performDenseToSparseTest(3, i, k);
}
