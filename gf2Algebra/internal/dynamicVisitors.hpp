#ifndef GF2ALGEBRA_INTERNAL_DYNAMICVISITORS_HPP
#define GF2ALGEBRA_INTERNAL_DYNAMICVISITORS_HPP

#include <boost/variant/static_visitor.hpp>
#include "../operations/copy.hpp"

namespace gf2Algebra {
namespace internal {

struct copy_visit : public boost::static_visitor<>
{
    template <typename T1, typename T2>
    void operator()(const T1 & source, T2 & target) const
    {
        copy(source, target);
    }
};

}
}

#endif // GF2ALGEBRA_INTERNAL_DYNAMICVISITORS_HPP

