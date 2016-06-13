#include <iostream>
#include "gf2Algebra.hpp"


SparseGroupAlgebra add(const SparseGroupAlgebra & s1, const SparseGroupAlgebra & s2) {
    std::vector<std::pair<int, Galois> > result;		// coefficients of the result of the additions

	if(s1.isZero())	return s2;
	if(s2.isZero())	return s1;

	// browse sorted vectors of coefficients of each element
	for (std::pair<SparseGroupAlgebra::iterator, SparseGroupAlgebra::iterator> it(s1.begin(), s2.begin());
			!(it.first == s1.end() && it.second == s2.end());) {
		if(it.first == s1.end()) {
			result.push_back((*it.second));
			it.second++;
		} else if (it.second == s2.end()) {
			result.push_back((*it.first));
			it.first++;
		} else {
			if ((*it.first).first == (*it.second).first) {
				// both coefficient are non zeros
				Galois sum = (*it.first).second + (*it.second).second;
				if (sum != Galois::zero) {
					result.push_back(std::make_pair((*it.first).first, sum));
				}
				it.first++;
				it.second++;
			} else {
				// only one is non zero
				if ((*it.first).first < (*it.second).first) {
					result.push_back(*it.first);
					it.first++;
				} else {
					result.push_back((*it.second));
					it.second++;
				}
			}
		}
	}

	return SparseGroupAlgebra(result);
}

/**
 * First quick and dirty implementation. TODO :
 */
SparseGroupAlgebra multiplySparse(const SparseGroupAlgebra & s1, const SparseGroupAlgebra & s2) {
    std::vector<std::pair<int, Galois> > products;

	if(s1.isZero())	return SparseGroupAlgebra();
	if(s2.isZero())	return SparseGroupAlgebra();

	int i;
	// first step : multiply of the terms and store the non zero ones in the vector
	for(SparseGroupAlgebra::iterator it1 = s1.begin(); it1 != s1.end(); it1++) {
		for(SparseGroupAlgebra::iterator it2 = s2.begin(); it2 != s2.end(); it2++) {
			i = (*it1).first^(*it2).first;
			if(i != 0) {
				products.push_back(std::pair<int, Galois>(i, (*it1).second * (*it2).second));
			}
		}
	}

	// sort the terms according to their indices
    std::sort(products.begin(), products.end());

	// add the coefficients of same indices
    std::vector<std::pair<int, Galois> > result;
	Galois sum;

	bool first = true;
    for(std::vector<std::pair<int, Galois> >::const_iterator it = products.begin(); it != products.end(); it++) {
		if(first) {
			i = (*it).first;
			sum = (*it).second;
			first = false;
		} else {
			if((*it).first == i) {
				sum += (*it).second;
			} else {
				if(sum != Galois::zero) {
					result.push_back(std::pair<int, Galois>(i, sum));
				}
				i = (*it).first;
				sum = (*it).second;
			}
		}
	}

	return SparseGroupAlgebra(result);
}

std::ostream& operator << (std::ostream& out, const SparseGroupAlgebra& s) {
	out << "S(";
	bool first =true;
    for(std::vector<SparseGroupAlgebra::data>::const_iterator s_it = s.begin(); s_it != s.end(); s_it++) {
		if(first)
			first = false;
		else
			out << ", ";
		out << "(" << (*s_it).first << ", " << (*s_it).second.polyRepresentation() << ")";
	}
	out << ")";
	return out;
}
