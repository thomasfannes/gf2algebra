#ifndef GF2ALGEBRA_INTERNAL_DYNAMICALGEBRA_HPP
#define GF2ALGEBRA_INTERNAL_DYNAMICALGEBRA_HPP

#include "dynamicElementImp.hpp"


namespace gf2Algebra {
namespace internal {

class DynamicAlgebra
{
public:
    // this value is the cut-off point to go from sparse to dense, and vice verse. We go from
    // sparse to dense if the number of non-zero coefficients is larger then
    // DEFAULT_C * sqrt(2^k)
    const static double DEFAULT_C = 1.0;

    // this constant is used to define the minimal value of k before we use the fft
    // optimization
    const static double DEFAULT_N = 6;


    DynamicAlgebra(double c = DEFAULT_C, std::size_t n = DEFAULT_N);

    void add(const DynamicElementImpl & lhs, const DynamicElementImpl & rhs, DynamicElementImpl & tgt) const;
    void addAssign(DynamicElementImpl & lhs, const DynamicElementImpl & rhs) const;
    void multiply(const DynamicElementImpl & lhs, const DynamicElementImpl & rhs, DynamicElementImpl & tgt) const;

protected:
    void updateRepresentation(const DynamicElementImpl & element) const;


private:
    double c;
    std::size_t n;
};

} // namespace internal
} // namespace gf2Algebra

#endif // GF2ALGEBRA_INTERNAL_DYNAMICALGEBRA_HPP
