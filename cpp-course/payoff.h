#ifndef __PAY_OFF_H
#define __PAY_OFF_H

#include <algorithm> // Needed for std::max comparison function

class PayOff {
public:
	PayOff(); // Default (no parameter) constructor
	virtual ~PayOff() {}; // Virtual destructor

	// Overloaded () operator
	// Turns PayOff into abstract function object
	// = 0 makes it pure virtual
	virtual double operator() (const double S) const = 0;
};

class PayOffCall : public PayOff {
private:
	double K; // Strike price
	
public:
	PayOffCall(const double K_);
	virtual ~PayOffCall() {};

	// Virtual function is now over-ridden (not pure-virtual anymore)
	virtual double operator() (const double S) const;
};

class PayOffPut : public PayOff {
private:
	double K; // Strike price

public:
	PayOffPut(const double K_);
	virtual ~PayOffPut() {};

	// Virtual function is now over-ridden (not pure-virtual anymore)
	virtual double operator() (const double S) const;
};

#endif