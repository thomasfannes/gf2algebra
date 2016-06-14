/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/


#include "io.hpp"
#include <ostream>

namespace gf2Algebra
{

std::ostream & operator << (std::ostream& out, const SparseElement& s)
{
    out << "S(";
    bool first = true;

    for(SparseElement::const_iterator s_it = s.begin(); s_it != s.end(); s_it++)
    {
        if(first)
            first = false;
        else
            out << ", ";

        const SparseElement::sparse_coefficient & el = *s_it;

        out << "(" << el.value.numRepresentation() << ", " << el.coefficient.polyRepresentation() << ")";
    }
    out << ")";
    return out;
}
} // namespace gf2Algebra

