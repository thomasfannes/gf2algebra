#define BOOST_TEST_MODULE TransformTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <gf2Algebra/ext/subsetIndexMap.hpp>
#include "util.hpp"

using namespace gf2Algebra;



BOOST_AUTO_TEST_CASE( subset_index_map_test )
{
    Bitset activeBits(52); // (110100b)
    SubsetIndexMap map(activeBits);

    BOOST_CHECK_EQUAL(map.fromGroupValue(Z2k(4)), 1);


}
