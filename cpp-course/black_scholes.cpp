#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include "black_scholes.h"
#include "european_monte_carlo.h"
#include <algorithm>    // Needed for the "max" function

// Standard normal probability density function
double norm_pdf(const double x)
{
	return (1.0 / (pow(2 * M_PI, 0.5))) * exp(-0.5 * x * x);
}

// An approximation to the cumulative distribution function
// for the standard normal distribution
// Note: This is a recursive function
double norm_cdf(const double x) {
    double k = 1.0 / (1.0 + 0.2316419 * x);
    double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

    if (x >= 0.0) {
        return (1.0 - (1.0 / (pow(2 * M_PI, 0.5))) * exp(-0.5 * x * x) * k_sum);
    }
    else {
        return 1.0 - norm_cdf(-x);
    }
}

// This calculates d_j, for j in {1,2}. This term appears in the closed
// form solution for the European call or put price
double d_j(const int j, const double S, const double K, const double r, const double v, const double T) {
    return (log(S / K) + (r + (pow(-1, j - 1)) * 0.5 * v * v) * T) / (v * (pow(T, 0.5)));
}

double call_price(const double S, const double K, const double r, const double v, const double T)
{
    return S * norm_cdf(d_j(1, S, K, r, v, T)) - K * exp(-r * T) * norm_cdf(d_j(2, S, K, r, v, T));
}

double call_delta(const double S, const double K, const double r, const double v, const double T)
{
    return norm_cdf(d_j(1, S, K, r, v, T));
}

double call_gamma(const double S, const double K, const double r, const double v, const double T)
{
    return norm_pdf(d_j(1, S, K, r, v, T))/(S*v*sqrt(T));
}

double call_vega(const double S, const double K, const double r, const double v, const double T) 
{
    return S * norm_pdf(d_j(1, S, K, r, v, T)) * sqrt(T);
}

double call_theta(const double S, const double K, const double r, const double v, const double T) {
    return -(S * norm_pdf(d_j(1, S, K, r, v, T)) * v) / (2 * sqrt(T))
        - r * K * exp(-r * T) * norm_cdf(d_j(2, S, K, r, v, T));
}

double call_rho(const double S, const double K, const double r, const double v, const double T)
{
    return K * T * exp(-r * T) * norm_cdf(d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla put price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double put_price(const double S, const double K, const double r, const double v, const double T) {
    return -S * norm_cdf(-d_j(1, S, K, r, v, T)) + K * exp(-r * T) * norm_cdf(-d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla put Delta
double put_delta(const double S, const double K, const double r, const double v, const double T) {
    return norm_cdf(d_j(1, S, K, r, v, T)) - 1;
}

// Calculate the European vanilla put Gamma
double put_gamma(const double S, const double K, const double r, const double v, const double T) {
    return call_gamma(S, K, r, v, T); // Identical to call by put-call parity
}

// Calculate the European vanilla put Vega
double put_vega(const double S, const double K, const double r, const double v, const double T) {
    return call_vega(S, K, r, v, T); // Identical to call by put-call parity
}

// Calculate the European vanilla put Theta
double put_theta(const double S, const double K, const double r, const double v, const double T) {
    return -(S * norm_pdf(d_j(1, S, K, r, v, T)) * v) / (2 * sqrt(T))
        + r * K * exp(-r * T) * norm_cdf(-d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla put Rho
double put_rho(const double S, const double K, const double r, const double v, const double T) {
    return -T * K * exp(-r * T) * norm_cdf(-d_j(2, S, K, r, v, T));
}

// This uses the forward difference approximation to calculate the Delta of a call option
double call_delta_fdm(const double S, const double K, const double r, const double v, const double T, const double delta_S)
{
    return (call_price(S + delta_S, K, r, v, T) - call_price(S, K, r, v, T)) / delta_S;
}

// This uses the centred difference approximation to calculate the Gamma of a call option
double call_gamma_fdm(const double S, const double K, const double r, const double v, const double T, const double delta_S)
{
    return (call_price(S + delta_S, K, r, v, T) - 2 * call_price(S, K, r, v, T) + call_price(S - delta_S, K, r, v, T)) / (delta_S * delta_S);
}

// Pricing a European vanilla call option with a Monte Carlo method
// Create three separate paths, each with either an increment, non-
// increment or decrement based on delta_S, the stock path parameter
void monte_carlo_call_price(const int num_sims, const double S, const double K, const double r, const double v, const double T, const double delta_S, double& price_Sp, double& price_S, double& price_Sm)
{
    // Since we wish to use the same Gaussian random draws for each path, it is
  // necessary to create three separated adjusted stock paths for each 
  // increment/decrement of the asset
    double Sp_adjust = (S + delta_S) * exp(T * (r - 0.5 * v * v));
    double S_adjust = S * exp(T * (r - 0.5 * v * v));
    double Sm_adjust = (S - delta_S) * exp(T * (r - 0.5 * v * v));

    // These will store all three 'current' prices as the Monte Carlo
    // algorithm is carried out
    double Sp_cur = 0.0;
    double S_cur = 0.0;
    double Sm_cur = 0.0;

    // There are three separate pay-off sums for the final price
    double payoff_sum_p = 0.0;
    double payoff_sum = 0.0;
    double payoff_sum_m = 0.0;

    // Loop over the number of simulations
    for (int i = 0; i < num_sims; i++) {
        double gauss_bm = gaussian_box_muller(); // Random gaussian draw

        // Adjust three stock paths 
        double expgauss = exp(sqrt(v * v * T) * gauss_bm);  // Precalculate
        Sp_cur = Sp_adjust * expgauss;
        S_cur = S_adjust * expgauss;
        Sm_cur = Sm_adjust * expgauss;

        // Calculate the continual pay-off sum for each increment/decrement
        payoff_sum_p += std::max(Sp_cur - K, 0.0);
        payoff_sum += std::max(S_cur - K, 0.0);
        payoff_sum_m += std::max(Sm_cur - K, 0.0);
    }

    // There are three separate prices
    price_Sp = (payoff_sum_p / static_cast<double>(num_sims)) * exp(-r * T);
    price_S = (payoff_sum / static_cast<double>(num_sims)) * exp(-r * T);
    price_Sm = (payoff_sum_m / static_cast<double>(num_sims)) * exp(-r * T);
}

double call_delta_mc(const int num_sims, const double S, const double K, const double r, const double v, const double T, const double delta_S)
{
    // These values will be populated via the monte_carlo_call_price function.
    // They represent the incremented Sp (S+delta_S), non-incremented S (S) and
    // decremented Sm (S-delta_S) prices.
    double price_Sp = 0.0;
    double price_S = 0.0;
    double price_Sm = 0.0;

    // Call the Monte Carlo pricer for each of the three stock paths
    // (We only need two for the Delta)
    monte_carlo_call_price(num_sims, S, K, r, v, T, delta_S, price_Sp, price_S, price_Sm);
    return (price_Sp - price_S) / delta_S;
}

double call_gamma_mc(const int num_sims, const double S, const double K, const double r, const double v, const double T, const double delta_S)
{
    // These values will be populated via the monte_carlo_call_price function.
    // They represent the incremented Sp (S+delta_S), non-incremented S (S) and
    // decremented Sm (S-delta_S) prices.
    double price_Sp = 0.0;
    double price_S = 0.0;
    double price_Sm = 0.0;

    // Call the Monte Carlo pricer for each of the three stock paths
    // (We need all three for the Gamma) 
    monte_carlo_call_price(num_sims, S, K, r, v, T, delta_S, price_Sp, price_S, price_Sm);
    return (price_Sp - 2 * price_S + price_Sm) / (delta_S * delta_S);
}

void GreeksAnalyticExample()
{
    double S = 100.0;  // Option price
    double K = 100.0;  // Strike price
    double r = 0.05;   // Risk-free rate (5%)
    double v = 0.2;    // Volatility of the underlying (20%)
    double T = 1.0;    // One year until expiry

    // Then we calculate the call/put values and the Greeks
    double call = call_price(S, K, r, v, T);
    double call_delta_v = call_delta(S, K, r, v, T);
    double call_gamma_v = call_gamma(S, K, r, v, T);
    double call_vega_v = call_vega(S, K, r, v, T);
    double call_theta_v = call_theta(S, K, r, v, T);
    double call_rho_v = call_rho(S, K, r, v, T);

    double put = put_price(S, K, r, v, T);
    double put_delta_v = put_delta(S, K, r, v, T);
    double put_gamma_v = put_gamma(S, K, r, v, T);
    double put_vega_v = put_vega(S, K, r, v, T);
    double put_theta_v = put_theta(S, K, r, v, T);
    double put_rho_v = put_rho(S, K, r, v, T);

    // Finally we output the parameters and prices
    std::cout << "Underlying:      " << S << std::endl;
    std::cout << "Strike:          " << K << std::endl;
    std::cout << "Risk-Free Rate:  " << r << std::endl;
    std::cout << "Volatility:      " << v << std::endl;
    std::cout << "Maturity:        " << T << std::endl << std::endl;

    std::cout << "Call Price:      " << call << std::endl;
    std::cout << "Call Delta:      " << call_delta_v << std::endl;
    std::cout << "Call Gamma:      " << call_gamma_v << std::endl;
    std::cout << "Call Vega:       " << call_vega_v << std::endl;
    std::cout << "Call Theta:      " << call_theta_v << std::endl;
    std::cout << "Call Rho:        " << call_rho_v << std::endl << std::endl;

    std::cout << "Put Price:       " << put << std::endl;
    std::cout << "Put Delta:       " << put_delta_v << std::endl;
    std::cout << "Put Gamma:       " << put_gamma_v << std::endl;
    std::cout << "Put Vega:        " << put_vega_v << std::endl;
    std::cout << "Put Theta:       " << put_theta_v << std::endl;
    std::cout << "Put Rho:         " << put_rho_v << std::endl;
}

void GreeksFiniteDifferenceMethod()
{
    // First we create the parameter list
    double S = 100.0;        // Option price
    double delta_S = 0.001;  // Option price increment
    double K = 100.0;        // Strike price
    double r = 0.05;         // Risk-free rate (5%)
    double v = 0.2;          // Volatility of the underlying (20%)
    double T = 1.0;          // One year until expiry

    // Then we calculate the Delta and the Gamma for the call
    double call_delta_f = call_delta_fdm(S, K, r, v, T, delta_S);
    double call_gamma_f = call_gamma_fdm(S, K, r, v, T, delta_S);

    // Finally we output the parameters and greeks
    std::cout << "Underlying:        " << S << std::endl;
    std::cout << "Delta underlying:  " << delta_S << std::endl;
    std::cout << "Strike:            " << K << std::endl;
    std::cout << "Risk-Free Rate:    " << r << std::endl;
    std::cout << "Volatility:        " << v << std::endl;
    std::cout << "Maturity:          " << T << std::endl << std::endl;

    std::cout << "Call Delta:        " << call_delta_f << std::endl;
    std::cout << "Call Gamma:        " << call_gamma_f << std::endl;
}
