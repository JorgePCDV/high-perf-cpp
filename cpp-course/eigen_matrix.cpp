#include "eigen_matrix.h"
#include <iostream>
#include <Eigen/Dense>

void EigenMatrixMatrix()
{
	// Define a 3x3 matrix and two 3-dimensional vectors
	Eigen::Matrix3d p;
	p << 1, 2, 3,
		4, 5, 6,
		7, 8, 9;
	Eigen::Vector3d r(10, 11, 12);
	Eigen::Vector3d s(13, 14, 15);

	// Matrix/matrix multiplication
	std::cout << "p*p:\n" << p * p << std::endl;

	// Matrix/vector multiplication
	std::cout << "p*r:\n" << p * r << std::endl;
	std::cout << "r^T*p:\n" << r.transpose() * p << std::endl;

	// Vector/vector multiplication (inner product)
	std::cout << "r^T*s:\n" << r.transpose() * s << std::endl;

}

void EigenMatrixReduction()
{
	// Declare and initialise a 3D matrix
	Eigen::Matrix3d p;
	p << 1, 2, 3,
		4, 5, 6,
		7, 8, 9;
		
	// Output the reduction operations
	std::cout << "p.sum(): " << p.sum() << std::endl;
	std::cout << "p.prod(): " << p.prod() << std::endl;
	std::cout << "p.mean(): " << p.mean() << std::endl;
	std::cout << "p.minCoeff(): " << p.minCoeff() << std::endl;
	std::cout << "p.maxCoeff(): " << p.maxCoeff() << std::endl;
	std::cout << "p.trace(): " << p.trace() << std::endl;
}
