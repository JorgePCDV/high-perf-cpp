#ifndef __PAY_OFF_DOUBLE_DIGITAL_CPP
#define __PAY_OFF_DOUBLE_DIGITAL_CPP

#include "payoff_double_digital.h"

// Constructor with two strike parameters, upper and lower barrier
PayOffDoubleDigital::PayOffDoubleDigital(const double  _U, const double _D) {
	U = _U;
	D = _D;
}

// Destructor
PayOffDoubleDigital::~PayOffDoubleDigital() {}

// Over-ridden operator() method which turns PayOffDoubleDigital into a function object
double PayOffDoubleDigital::operator() (const double S) const {
	if (S >= D && S <= U) {
		return 1.0;
	} else {
		return 0.0;
	}
}

#endif