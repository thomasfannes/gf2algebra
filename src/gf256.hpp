/*******************************************************************
* Copyright (c) 2010-2013 MiGraNT - DTAI.cs.kuleuven.be
* License details in the root directory of this distribution in
* the LICENSE file
********************************************************************/

#ifndef GF2ALGEBRA_GF256_HPP
#define GF2ALGEBRA_GF256_HPP

#include <string>

namespace gf2Algebra {

/*
 * Element of the Galois Field of size 2^N = GF(256)
 */
class GF256
{
    typedef unsigned char storage_type;

public:
    static const std::size_t CHARACTERISTIC = 2;
    static const std::size_t POWER = 8;
    static const std::size_t ORDER = 256;


	// constructors
    GF256() : _m(0) {	}
    explicit GF256(storage_type m) : _m(m){  }
    GF256(const GF256 & rhs) : _m(rhs._m) { }

	// assignment operator
    GF256 & operator=(const GF256 & rhs);

	// addition assignment
    GF256 & operator+=(const GF256 & rhs);

	// addition and multiplication
    GF256 operator+(const GF256 & rhs) const;
    GF256 operator*(const GF256 & rhs) const;

	// equality
    bool operator==(const GF256 & rhs) const;
    bool operator!=(const GF256 & rhs) const;

	// information functions
	std::string polyRepresentation() const;

    static const GF256 zero;

	// swap function for efficient use in stl
   friend void swap(GF256 & lhs, GF256 & rhs);

private:
    storage_type _m;

};


} // gf2Algebra namespace

#endif // GF2ALGEBRA_GF256_HPP



