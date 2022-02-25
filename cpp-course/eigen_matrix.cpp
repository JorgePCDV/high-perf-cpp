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

// Vectors a, b, c and d are const. They will not be modified
// by the function. Vector f (the solution vector) is non-const
// and thus will be calculated and updated by the function.
void thomas_algorithm(const std::vector<double>& a, 
					  const std::vector<double>& b, 
					  const std::vector<double>& c, 
					  const std::vector<double>& d, 
					  std::vector<double>& f)
{
	size_t N = d.size();

	// Create the temporary vectors
	// Note that this is inefficient as it is possible to call
	// this function many times. A better implementation would
	// pass these temporary matrices by non-const reference to
	// save excess allocation and deallocation
	std::vector<double> c_star(N, 0.0);
	std::vector<double> d_star(N, 0.0);

	// This updates the coefficients in the first row
	// Note that we should be checking for division by zero here
	c_star[0] = c[0] / b[0];
	d_star[0] = d[0] / b[0];

	// Create the c_star and d_star coefficients in the forward sweep
	for (int i = 1; i < N; i++) {
		double m = 1.0 / (b[i] - a[i] * c_star[i - 1]);
		c_star[i] = c[i] * m;
		d_star[i] = (d[i] - a[i] * d_star[i - 1]) * m;
	}

	// This is the reverse sweep, used to update the solution vector f
	for (int i = N - 1; i > 0; i--) {
		f[i] = d_star[i] - c_star[i] * d[i + 1];
	}
}

void ThomasAlgorithmExample()
{
	// Create a Finite Difference Method (FDM) mesh with 13 points
  // using the Crank-Nicolson method to solve the discretised
  // heat equation.
	size_t N = 13;
	double delta_x = 1.0 / static_cast<double>(N);
	double delta_t = 0.001;
	double r = delta_t / (delta_x * delta_x);

	// First we create the vectors to store the coefficients
	std::vector<double> a(N - 1, -r / 2.0);
	std::vector<double> b(N, 1.0 + r);
	std::vector<double> c(N - 1, -r / 2.0);
	std::vector<double> d(N, 0.0);
	std::vector<double> f(N, 0.0);

	// Fill in the current time step initial value
	// vector using three peaks with various amplitudes
	f[5] = 1; f[6] = 2; f[7] = 1;

	// We output the solution vector f, prior to a
	// new time-step
	std::cout << "f = (";
	for (int i = 0; i < N; i++) {
		std::cout << f[i];
		if (i < N - 1) {
			std::cout << ", ";
		}
	}
	std::cout << ")" << std::endl << std::endl;

	// Fill in the current time step vector d
	for (int i = 1; i < N - 1; i++) {
		d[i] = r * 0.5 * f[i + 1] + (1.0 - r) * f[i] + r * 0.5 * f[i - 1];
	}

	// Now we solve the tridiagonal system
	thomas_algorithm(a, b, c, d, f);

	// Finally we output the solution vector f
	std::cout << "f = (";
	for (int i = 0; i < N; i++) {
		std::cout << f[i];
		if (i < N - 1) {
			std::cout << ", ";
		}
	}
	std::cout << ")" << std::endl;
}
