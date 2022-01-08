#ifndef __PAY_OFF_H
#define __PAY_OFF_H

#include <algorithm> // Needed for std::max comparison function

class PayOff {
	public:
		Payoff(); // Default (no parameter) constructor
		virtual ~PayOff() {}; // Virtual destructor

		// Overloaded () operator
		// Turns PayOff into abstract function object
		// = 0 makes it pure virtual
		virtual double operator() (const double S) const = 0;
};

#endif