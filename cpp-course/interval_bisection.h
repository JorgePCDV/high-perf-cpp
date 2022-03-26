#pragma once
#ifndef __INTERVAL_BISECTION_H
#define __INTERVAL_BISECTION_H

#include <cmath>

// Creating a function template
// Trying to find an x such that |g(x) - y| < epsilon,
// starting with the interval (m, n).
template<typename T>
double interval_bisection(double y_target,  // Target y value
	double m,         // Left interval value
	double n,         // Right interval value
	double epsilon,   // Tolerance
	T g) {            // Function object of type T, named g

// Create the initial x mid-point value
// Find the mapped y value of g(x)
	double x = 0.5 * (m + n);
	double y = g(x);

	// While the difference between y and the y_target
	// value is greater than epsilon, keep subdividing
	// the interval into successively smaller halves
	// and re-evaluate the new y.
	do {
		if (y < y_target) {
			m = x;
		}

		if (y > y_target) {
			n = x;
		}

		x = 0.5 * (m + n);
		y = g(x);
	} while (fabs(y - y_target) > epsilon);

	return x;
}

void IntervalBisectionExample() {
	// First we create the parameter list
	double S = 100.0;  // Underlying spot price
	double K = 100.0;  // Strike price
	double r = 0.05;   // Risk-free rate (5%)
	double T = 1.0;    // One year until expiry
	double C_M = 10.5; // Option market price

	// Create the Black-Scholes Call functor
	BlackScholesCall bsc(S, K, r, T);

	// Interval Bisection parameters
	double low_vol = 0.05;
	double high_vol = 0.35;
	double episilon = 0.001;

	// Calculate the implied volatility
	double sigma = interval_bisection(C_M, low_vol, high_vol, episilon, bsc);

	// Output the values
	std::cout << "Implied Vol: " << sigma << std::endl;
}

#endif
