#include "binary_function.h"

BinaryFunction::BinaryFunction() {}

Add::Add() {}

double Add::operator() (double left, double right)
{
	return left + right;
}

Multiply::Multiply() {}

double Multiply::operator()(double left, double right)
{
	return left * right;
}

double binary_op(double left, double right, BinaryFunction* bin_func)
{
	return (*bin_func)(left, right);
}

void BinaryFunctionExample()
{
	double a = 5.0;
	double b = 10.0;

	BinaryFunction* pAdd = new Add();
	BinaryFunction* pMultiply = new Multiply();

	std::cout << "Add: " << binary_op(a, b, pAdd) << std::endl;
	std::cout << "Multiply: " << binary_op(a, b, pMultiply) << std::endl;

	delete pAdd;
	delete pMultiply;
}
