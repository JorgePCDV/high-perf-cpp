#include <vector>

void EigenMatrixMatrix();
void EigenMatrixReduction();
void EigenMatrixScalarArithmetic();
void EigenMatrixTransposition();
void EigenMatrixVector();

void EigenLuDecomposition();

void thomas_algorithm(const std::vector<double>& a,
					  const std::vector<double>& b,
					  const std::vector<double>& c,
					  const std::vector<double>& d,
					  std::vector<double>& f);
void ThomasAlgorithmExample();

void CholeskyDecomposition();
