#ifndef GF2ALGEBRA_INTERNAL_DYNAMICVISITORS_HPP
#define GF2ALGEBRA_INTERNAL_DYNAMICVISITORS_HPP

#include <boost/variant/static_visitor.hpp>
#include "../operations/copy.hpp"
#include "../operations/addition.hpp"
#include "../operations/additionAssignment.hpp"
#include "../operations/multiplication.hpp"

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

struct add_visit : public boost::static_visitor<>
{
    template <typename T1, typename T2, typename T3>
    void operator()(const T1 & lhs, const T2 & rhs, T3 & tgt) const
    {
        add(lhs, rhs, tgt);
    }
};

struct add_assign_visit : public boost::static_visitor<>
{
    template <typename T1, typename T2>
    void operator()(T1 & lhs, const T2 & rhs) const
    {
        addAssign(lhs, rhs);
    }
};

struct multiplication_visit : public boost::static_visitor<>
{
    template <typename T1, typename T2, typename T3>
    void operator()(const T1 & lhs, const T2 & rhs, T3 & tgt) const
    {
        multiply(lhs, rhs, tgt);
    }
};

struct count_nonzero_visit : public boost::static_visitor<std::size_t>
{
    template <typename T>
    std::size_t operator()(const T & element) const
    {
        return countNonZero(element);
    }
};

struct iszero_visit : public boost::static_visitor<bool>
{
    template <typename T>
    bool operator()(const T & element) const
    {
        return isZero(element);
    }
};

}
}

#endif // GF2ALGEBRA_INTERNAL_DYNAMICVISITORS_HPP

