#include <vector>
#include <iostream>
#include <utility>

#include "galoisFields.hpp"

/*
 * Group algebra GF(2^8)[Z_2^k]
 */
class SparseGroupAlgebra {
public:
	typedef std::pair<int, Galois> data; // TODO : find a better name / TODO : choose the convenient data types
	SparseGroupAlgebra() {

	}

	SparseGroupAlgebra (std::vector<data> coefficients) : _coefficients(coefficients) {
		std::sort(_coefficients.begin(), _coefficients.end(), [](data a, data b) {
			return a.first < b.first;
		});
	}

	bool isZero() const {
		return _coefficients.size() == 0;
	}

	std::size_t countNonZero() {
		return _coefficients.size();
	}

	//typedef std::vector<data>::iterator iterator;
	typedef std::vector<data>::const_iterator iterator;
	iterator begin() const { return _coefficients.begin(); }
	iterator end() const { return _coefficients.end(); }

	//friend std::ostream& operator<<(std::ostream& out, const SparseGroupAlgebra& s);

private:
	std::vector<data> _coefficients;

};

std::ostream& operator<<(std::ostream &out, const SparseGroupAlgebra& s);
SparseGroupAlgebra add(const SparseGroupAlgebra & s1, const SparseGroupAlgebra & s2);
SparseGroupAlgebra multiplySparse(const SparseGroupAlgebra & s1, const SparseGroupAlgebra & s2);
