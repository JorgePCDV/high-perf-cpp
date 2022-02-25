#include "eigen_matrix.h"
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>

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

void EigenMatrixScalarArithmetic()
{
	// Define two matrices, both 3x3
	Eigen::Matrix3d p;
	Eigen::Matrix3d q;

	// Define two three-dimensional vectors
	Eigen::Vector3d r(1,2,3);
	Eigen::Vector3d s(4, 5, 6);

	p << 1, 2, 3,
		4, 5, 6,
		7, 8, 9;
	q << 10, 11, 12,
		13, 14, 15,
		16, 17, 18;

	// Output arithmetic operations for matrices
	std::cout << "p+q=\n" << p + q << std::endl;
	std::cout << "p-q=\n" << p - q << std::endl;

	// Output arithmetic operations for vectors
	std::cout << "r+s=\n" << r + s << std::endl;
	std::cout << "r-s=\n" << r - s << std::endl;
}

void EigenMatrixTransposition()
{
	// Declare a 3x3 matrix with random entries
	Eigen::Matrix3d p = Eigen::Matrix3d::Random(3, 3);

	std::cout << "p^T =\n" << p.transpose() << std::endl;
	
	p.transposeInPlace();

	// Output the in-place transpose of p
	std::cout << "p^T =\n" << p << std::endl;
}

void EigenMatrixVector()
{
	Eigen::Vector3d r(10,20,30);
	Eigen::Vector3d s(40,50,60);

	// Apply dot and cross products
	std::cout << "r . s=\n" << r.dot(s) << std::endl;
	std::cout << "r x s=\n" << r.cross(s) << std::endl;
}

void EigenLuDecomposition()
{
	typedef Eigen::Matrix<double, 4, 4> Matrix4x4;

	// Declare a 4x4 matrix with defined entries
	Matrix4x4 p;
	p << 7, 3, -1, 2,
		3, 8, 1, -4,
		-1, 1, 4, -1,
		2, -4, -1, 6;
	std::cout << "Matrix P:\n" << p << std::endl << std::endl;

	// Create LU decomposition template object for p
	Eigen::PartialPivLU<Matrix4x4> lu(p);
	std::cout << "LU Matrix:\n" << lu.matrixLU() << std::endl << std::endl;

	// Output L, the lower triangular matrix
	Matrix4x4 l = Eigen::MatrixXd::Identity(4, 4);
	l.block<4, 4>(0, 0).triangularView<Eigen::StrictlyLower>() = lu.matrixLU();
	std::cout << "L Matrix:\n" << l << std::endl << std::endl;

	// Output U, the upper triangular matrix
	Matrix4x4 u = lu.matrixLU().triangularView<Eigen::Upper>();
	std::cout << "R Matrix:\n" << u << std::endl;
}
