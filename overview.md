Overview
========

This repository represents the elements and the algebraic operations on elements of the group ring of 
Z<sub>2</sub><sup>k</sup> on the galois field of order 2<sup>8</sup>. This library contains:
 - three different representations of those elements
 - algebraic operations between elements:
    - addition
    - scalar multiplication
    - elementwise multiplication
 - projections from Z<sub>2</sub><sup>k</sup> to Z<sub>2</sub><sup>l</sup>

Terminology
===========
For every element in our group ring, each value of Z<sub>2</sub><sup>k</sup> has a corresponding coefficient in the 
galois field 2<sup>8</sup>. For an element *a* of our group ring and a value *g* of Z<sub>2</sub><sup>k</sup>, we denote 
the coefficient of *g* in *a* with a<sub>g</sub>.


Different representations
=========================

Dense representation
--------------------
A trivial implementation has 2<sup>k</sup> coeffients, i.e., one for each possible element in Z<sub>2</sub><sup>k</sup>.


Sparse representation
---------------------
As the number of coefficients in an algebra element is exponential in parameter *k* and possibly many coefficients can be 
zero, we have a sparse representation of such an element. Only non-zero coefficients are stored.


Semi-dense representation
-------------------------
Let us first define the concept of an unused bit for an element of our group ring: If for every *g* in Z<sub>2</sub><sup>k</sup>
where the i<sup>th</sup> bit is one, the corresponding coefficient a<sub>g</sub> is zero, then we say that the i<sup>th</sup>
bit is unused. The semi-dense representation makes it possible to store dense elements but with a number of 
unused bits. 
