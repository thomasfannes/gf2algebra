#include <gf2Algebra/ext/representation.hpp>
#include <gf2Algebra/ext/multiplication.hpp>
#include <gf2Algebra/ext/identityIndexMap.hpp>

#include <boost/lexical_cast.hpp>

#include <ctime>
#include <utility>

using namespace gf2Algebra;
using namespace gf2Algebra::ext;

template <bool USEFFT>
double multiply(unsigned char k, const DenseRepresentation & lhs, const DenseRepresentation & rhs)
{
    DenseRepresentation tgt;
    initialize(tgt, k);
    clock_t time;


    time = std::clock();
    if(USEFFT)
        multiply_FFT(k, lhs, rhs, tgt, IdentityIndexMap(), IdentityIndexMap(), IdentityIndexMap());
    else
        multiply_quadratic(lhs, rhs, tgt, IdentityIndexMap(), IdentityIndexMap(), IdentityIndexMap());

    time = std::clock() - time;

    return static_cast<double>(time) / CLOCKS_PER_SEC;
}

void initialize(unsigned char k, DenseRepresentation & element)
{
    initialize(element, k);
    std::size_t k2 = (1 << k);

    for(std::size_t i = 0; i < k2; ++i)
        element[i] = GaloisField(std::rand() & 255);
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

    std::cout << "k;fft;quadratic" << std::endl;

    for(std::size_t k = 0; k <= max_k; ++k)
    {
        double fft_time = 0, qua_time = 0;

        for(std::size_t i = 0; i < max_runs; ++i)
        {
            // create some elements
            DenseRepresentation lhs, rhs;
            initialize(k, lhs);
            initialize(k, rhs);

            fft_time += multiply<true>(k, lhs, rhs);
            qua_time += multiply<false>(k, lhs, rhs);
        }

        std::cout << k << ";" << fft_time/max_runs << ";" << qua_time / max_runs << std::endl;
    }

}
