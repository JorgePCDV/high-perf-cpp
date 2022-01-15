#ifndef __SIMPLE_MATRIX_H
#define __SIMPLE_MATRIX_H

#include <vector> // Need this to store matrix values

template <typename Type = double>
class SimpleMatrix {
private:
	// Use vector of vectors to store the values
	std::vector<std::vector<Type>> mat;

public:
	SimpleMatrix(); // Default constructor

	// Constructor specifying rows columns and a default value
	SimpleMatrix(const int& rows, const int& cols, const Type& val);

	// Copy constructor
	SimpleMatrix(const SimpleMatrix<Type>& _rhs);

	// Assignment operator overloaded
	SimpleMatrix<Type>& operator= (const SimpleMatrix<Type>& _rhs);

	virtual ~SimpleMatrix(); // Destructor

	// Access to the matrix values directly, via row and column indices
	std::vector<std::vector<Type> > get_mat() const;
	Type& value(const int& row, const int& col);
};

#include "simple_matrix.cpp"

#endif
