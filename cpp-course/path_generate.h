#pragma once

#ifndef __PATH_GENERATION_H
#define __PATH_GENERATION_H

#include <vector>
#include <cmath>
#include "european_monte_carlo.h"


// This provides a vector containing sampled points of a 
// Geometric Brownian Motion stock price path
void calc_path_spot_prices(std::vector<double>& spot_prices,  // Vector of spot prices to be filled in
    const double& r,   // Risk free interest rate (constant)
    const double& v,   // Volatility of underlying (constant)
    const double& T) { // Expiry
// Since the drift and volatility of the asset are constant
// we will precalculate as much as possible for maximum efficiency
    double dt = T / static_cast<double>(spot_prices.size());
    double drift = exp(dt * (r - 0.5 * v * v));
    double vol = sqrt(v * v * dt);

    for (int i = 1; i < spot_prices.size(); i++) {
        double gauss_bm = gaussian_box_muller();
        spot_prices[i] = spot_prices[i - 1] * drift * exp(vol * gauss_bm);
    }
}

#endif