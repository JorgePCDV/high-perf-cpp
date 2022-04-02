#ifndef __NEWTON_RAPHSON_H
#define __NEWTON_RAPHSON_H

#include <cmath>
#include "black_scholes.h"
#include "newton_raphson.h"
#include <iostream>

template<typename T,
    double (T::* g)(double) const,
    double (T::* g_prime)(double) const>
    double newton_raphson(double y_target,       // Target y value
        double init,           // Initial x value
        double epsilon,        // Tolerance
        const T& root_func) {  // Function objec
// 
    double y = (root_func.*g)(init);
    double x = init;

    //
    while (fabs(y - y_target) > epsilon) {
        double d_x = (root_func.*g_prime)(x);
        x += (y_target - y) / d_x;
        y = (root_func.*g)(x);
    }
    return x;
}

void NewtonRaphsonExample() {
    // First we create the parameter list
    double S = 100.0;  // Underlying spot price
    double K = 100.0;  // Strike price
    double r = 0.05;   // Risk-free rate (5%)
    double T = 1.0;    // One year until expiry
    double C_M = 10.5; // Option market price

    // Create the Black-Scholes Call functor
    BlackScholesCall bsc(S, K, r, T);

    // Newton Raphson parameters
    double init = 0.3;  // Our guess impl. vol of 30%
    double epsilon = 0.001;

    // Calculate the implied volatility
    double sigma = newton_raphson<BlackScholesCall,
        &BlackScholesCall::option_price,
        &BlackScholesCall::option_vega>(C_M, init, epsilon, bsc);

    // Output the values
    std::cout << "Implied Vol: " << sigma << std::endl;
}

#endif