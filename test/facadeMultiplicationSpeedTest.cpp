#include <gf2Algebra/dynamicElement.hpp>
#include <boost/lexical_cast.hpp>

#include <ctime>
#include <utility>
#include <iostream>

using namespace gf2Algebra;

double multiply(const DynamicElement & lhs, const DynamicElement & rhs)
{
    clock_t time;

    {
        time = std::clock();
        DynamicElement tgt = lhs * rhs;
        time = std::clock() - time;
    }

    return static_cast<double>(time) / CLOCKS_PER_SEC;
}

void initialize(unsigned char k, DynamicElement & element)
{
    std::size_t k2 = (1 << k);

    for(std::size_t i = 0; i < k2; ++i)
        element.setCoefficient(Z2k(i), GaloisField(std::rand() & 255));
}

double performRun(unsigned char k, std::size_t noTries)
{
    Bitset bitset((1<<k) -1 );

    double time = 0;

    for(std::size_t i = 0; i < noTries; ++i)
    {
        DynamicElement lhs(bitset, DenseStorage), rhs(bitset, DenseStorage);

        // create some elements
        initialize(k, lhs);
        initialize(k, rhs);

        time += multiply(lhs, rhs);
    }

    return time / noTries;
}



int main(int argc, char ** argv)
{
    if(argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " max_k number_of_runs" << std::endl;
        return -1;
    }

    std::size_t max_k = boost::lexical_cast<std::size_t>(argv[1]);
    std::size_t max_runs = boost::lexical_cast<std::size_t>(argv[2]);

    std::cout << "k;time" << std::endl;

    for(std::size_t k = 0; k <= max_k; ++k)
        std::cout << k << ";" << performRun(k, max_runs) << std::endl;
}
