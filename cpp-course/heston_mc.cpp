#ifndef __HESTON_MC_CPP
#define __HESTON_MC_CPP

//#include <iostream>
#include "heston_mc.h"

// HestonEuler
// ===========

HestonEuler::HestonEuler(Option* _pOption,
    double _kappa, double _theta,
    double _xi, double _rho) :
    pOption(_pOption), kappa(_kappa), theta(_theta), xi(_xi), rho(_rho) {}

HestonEuler::~HestonEuler() {}

void HestonEuler::calc_vol_path(const std::vector<double>& vol_draws,
    std::vector<double>& vol_path) {
    size_t vec_size = vol_draws.size();
    double dt = pOption->T / static_cast<double>(vec_size);

    //std::cout << "Vec, dt: " << vec_size << ", " << dt << std::endl;

    // Iterate through the correlated random draws vector and
    // use the 'Full Truncation' scheme to create the volatility path
    for (int i = 1; i < vec_size; i++) {
        double v_max = std::max(vol_path[i - 1], 0.0);
        vol_path[i] = vol_path[i - 1] + kappa * dt * (theta - v_max) +
            xi * sqrt(v_max * dt) * vol_draws[i - 1];
    }
}

void HestonEuler::calc_spot_path(const std::vector<double>& spot_draws,
    const std::vector<double>& vol_path,
    std::vector<double>& spot_path) {
    size_t vec_size = spot_draws.size();
    double dt = pOption->T / static_cast<double>(vec_size);

    // Create the spot price path making use of the volatility
    // path. Uses a similar Euler Truncation method to the vol path.
    for (int i = 1; i < vec_size; i++) {
        double v_max = std::max(vol_path[i - 1], 0.0);
        spot_path[i] = spot_path[i - 1] * exp((pOption->r - 0.5 * v_max) * dt +
            sqrt(v_max * dt) * spot_draws[i - 1]);
    }
}

#endif

void generate_normal_correlation_paths(double rho, std::vector<double>& spot_normals, std::vector<double>& cor_normals)
{
    unsigned vals = spot_normals.size();

    // Create the Standard Normal Distribution and random draw vectors
    StandardNormalDistribution snd;
    std::vector<double> snd_uniform_draws(vals, 0.0);

    // Simple random number generation method based on RAND
    for (int i = 0; i < snd_uniform_draws.size(); i++) {
        snd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
    }

    // Create standard normal random draws
    snd.random_draws(snd_uniform_draws, spot_normals);

    // Create the correlated standard normal distribution
    CorrelatedSND csnd(rho, &spot_normals);
    std::vector<double> csnd_uniform_draws(vals, 0.0);

    // Uniform generation for the correlated SND
    for (int i = 0; i < csnd_uniform_draws.size(); i++) {
        csnd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
    }

    // Now create the -correlated- standard normal draw series
    csnd.random_draws(csnd_uniform_draws, cor_normals);
}

void HestonMcExample()
{
    // First we create the parameter list
  // Note that you could easily modify this code to input the parameters
  // either from the command line or via a file
    unsigned num_sims = 1000;   // Number of simulated asset paths
    unsigned num_intervals = 1000;  // Number of intervals for the asset path to be sampled 

    double S_0 = 100.0;    // Initial spot price
    double K = 100.0;      // Strike price
    double r = 0.0319;     // Risk-free rate
    double v_0 = 0.010201; // Initial volatility 
    double T = 1.00;       // One year until expiry

    double rho = -0.7;     // Correlation of asset and volatility
    double kappa = 6.21;   // 
    double theta = 0.019;  // 
    double xi = 0.61;      // "Vol of vol"

    // Create the PayOff, Option and Heston objects
    PayOff* pPayOffCall = new PayOffCall(K);
    Option* pOption = new Option(K, r, T, pPayOffCall);
    HestonEuler hest_euler(pOption, kappa, theta, xi, rho);

    // Create the spot and vol initial normal and price paths
    std::vector<double> spot_draws(num_intervals, 0.0);  // Vector of initial spot normal draws
    std::vector<double> vol_draws(num_intervals, 0.0);   // Vector of initial correlated vol normal draws
    std::vector<double> spot_prices(num_intervals, S_0);  // Vector of initial spot prices
    std::vector<double> vol_prices(num_intervals, v_0);   // Vector of initial vol prices

    // Monte Carlo options pricing
    double payoff_sum = 0.0;
    for (unsigned i = 0; i < num_sims; i++) {
        std::cout << "Calculating path " << i + 1 << " of " << num_sims << std::endl;
        generate_normal_correlation_paths(rho, spot_draws, vol_draws);
        hest_euler.calc_vol_path(vol_draws, vol_prices);
        hest_euler.calc_spot_path(spot_draws, vol_prices, spot_prices);
        payoff_sum += pOption->pay_off->operator()(spot_prices[num_intervals - 1]);
    }
    double option_price = (payoff_sum / static_cast<double>(num_sims)) * exp(-r * T);
    std::cout << "Option Price: " << option_price << std::endl;

    // Free memory
    delete pOption;
    delete pPayOffCall;
}
