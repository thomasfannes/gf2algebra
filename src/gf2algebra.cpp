#include <iostream>
#include "gf2algebra.hpp"

// assignment operator
Galois & Galois::operator=(const Galois & rhs) {
	if (this != &rhs) {
		Galois tmp(rhs);
		swap(*this, tmp);
	}
	return *this;
}

// addition assignment
Galois & Galois::operator+=(const Galois & rhs) {
	_m ^= rhs._m;
	return *this;
}


// addition and multiplication
Galois Galois::operator+(const Galois & rhs) const {
	return Galois(_m ^ rhs._m);
}
Galois Galois::operator*(const Galois & rhs) const {
	int t=0;
	if(_m == 0 || rhs._m == 0)	return 0;
	t = L[_m] + L[rhs._m];
	if(t > GF_ORDER-1) t -= (GF_ORDER - 1);
	return Galois(E[t]);
}

// equality
bool Galois::operator==(const Galois & rhs) const {
	return _m == rhs._m;
}
bool Galois::operator!=(const Galois & rhs) const {
	return _m != rhs._m;
}

// information functions
std::string Galois::polyRepresentation() const {
	std::stringstream str;
	bool first = true;
	for (int i = N-1; i >= 0; i--) {
		if (_m & (1 << i)) {
			if (first)
				first = false;
			else
				str << "+";
			switch (i) {
				case 0:
					str << "1";
					break;
				case 1:
					str << "x";
					break;
				default:
					str << "x^" << i;
					break;
			}
		}
	}
	std::string s = str.str();
	if(s == "")	s="0";
	return s;
}

// swap function for efficient use in stl
void swap(Galois & lhs, Galois & rhs) {
	std::swap(lhs._m, rhs._m);
}





