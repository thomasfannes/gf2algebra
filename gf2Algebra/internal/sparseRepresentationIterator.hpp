/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_INTERNAL_SPARSEREPRESENTATIONITERATO_HPP
#define GF2ALGEBRA_INTERNAL_SPARSEREPRESENTATIONITERATO_HPP

#include "../representation.hpp"

namespace gf2Algebra {
namespace internal {

struct SparseRepresentationOrderedAdder
{
    explicit SparseRepresentationOrderedAdder(SparseRepresentation & x)
        : container(&x)
    {
    }

    void operator()(const ValueCoefficientPair & vcp) const
    {
        if(vcp.coefficient != GaloisField::zero)
            container->push_back(vcp);
    }

protected:
    SparseRepresentation * container;
};

struct SparseRepresentationUnorderedAdder
{
    explicit SparseRepresentationUnorderedAdder(SparseRepresentation & x);
    ~SparseRepresentationUnorderedAdder();


    void operator()(const ValueCoefficientPair & vcp) const;
    void finalize();

protected:
    SparseRepresentation * container;
    mutable bool finished;
};

} // namespace internal
} // namespace gf2Algebra

#endif // GF2ALGEBRA_INTERNAL_SPARSEREPRESENTATIONITERATO_HPP
