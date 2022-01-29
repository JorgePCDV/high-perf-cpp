#include <iostream>

// Abstract base class
class BinaryFunction {
public:
	BinaryFunction();
	virtual double operator() (double left, double right) = 0;
};

class Add : public BinaryFunction {
public:
	Add();
	virtual double operator() (double left, double right);
};

class Multiply : public BinaryFunction {
public:
	Multiply();
	virtual double operator() (double left, double right);
};

double binary_op(double left, double right, BinaryFunction* bin_func);

void BinaryFunctionExample();

