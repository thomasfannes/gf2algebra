#ifndef GF2ALGEBRA_DYNAMICELEMENT_HPP
#define GF2ALGEBRA_DYNAMICELEMENT_HPP

#include <bitset>
#include "config.hpp"

namespace gf2Algebra {

/**
 * @brief The DynamicElement class
 */
class DynamicElement
{
public:
    DynamicElement();

private:
    std::bitset<MAX_K_VALUE> activeBits_;

};

} // namespace gf2Algebra

#endif // GF2ALGEBRA_DYNAMICELEMENT_HPP
