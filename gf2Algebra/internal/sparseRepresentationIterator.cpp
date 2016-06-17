/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#include "sparseRepresentationIterator.hpp"
#include <algorithm>

namespace gf2Algebra {
namespace internal {



SparseRepresentationUnorderedAdder::SparseRepresentationUnorderedAdder(SparseRepresentation & x)
    : container(&x),
      finished(true)
{
}

SparseRepresentationUnorderedAdder::~SparseRepresentationUnorderedAdder()
{
    if(!finished)
        finalize();
}


void SparseRepresentationUnorderedAdder::operator()(const ValueCoefficientPair & vcp) const
{
    if(vcp.coefficient != GaloisField::zero)
    {
        container->push_back(vcp);
        finished = false;
    }
}

void SparseRepresentationUnorderedAdder::finalize()
{
    // sort everything
    std::sort(container->begin(), container->end());


    SparseRepresentation::const_iterator readIt = container->begin();
    SparseRepresentation::iterator writeIt = container->begin();

    while(readIt != container->end())
    {
        // set the current
        ValueCoefficientPair cur = *readIt++;

        // continue over all similar elements
        while(readIt != container->end() && readIt->value == cur.value)
            cur += *readIt++;

        // and if nonzero, add it
        if(cur.coefficient != GaloisField::zero)
            *writeIt++ = cur;
    }

    // and cleanup
    container->erase(writeIt, container->end());
}

} // internal namespace
} // gf2Algebra namespace
