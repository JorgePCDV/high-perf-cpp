#ifndef __CORRELATED_SND_CPP
#define __CORRELATED_SND_CPP
#define _USE_MATH_DEFINES


#include "correlated_snd.h"
#include <iostream>
#include <cmath>

CorrelatedSND::CorrelatedSND(const double _rho,
    const std::vector<double>* _uncorr_draws)
    : rho(_rho), uncorr_draws(_uncorr_draws) {}

CorrelatedSND::~CorrelatedSND() {}

void CorrelatedSND::correlation_calc(std::vector<double>& dist_draws) {
    for (int i = 0; i < dist_draws.size(); i++) {
        dist_draws[i] = rho * (*uncorr_draws)[i] + dist_draws[i] * sqrt(1 - rho * rho);
    }
}

void CorrelatedSND::random_draws(const std::vector<double>& uniform_draws,
    std::vector<double>& dist_draws) {
    if (uniform_draws.size() != dist_draws.size()) {
        std::cout << "Draws vectors are of unequal size in standard normal dist." << std::endl;
        return;
    }

    if (uniform_draws.size() % 2 != 0) {
        std::cout << "Uniform draw vector size not an even number." << std::endl;
        return;
    }

    for (int i = 0; i < uniform_draws.size() / 2; i++) {
        dist_draws[2 * i] = sqrt(-2.0 * log(uniform_draws[2 * i])) * sin(2 * M_PI * uniform_draws[2 * i + 1]);
        dist_draws[2 * i + 1] = sqrt(-2.0 * log(uniform_draws[2 * i])) * cos(2 * M_PI * uniform_draws[2 * i + 1]);
    }

    // Modify the random draws via the correlation calculation
    correlation_calc(dist_draws);

    return;
}

#endif

void CorrelatedSndExample()
{
    int vals = 30;

    // Create the Standard Normal Distribution and random draw vectors
    StandardNormalDistribution snd;
    std::vector<double> snd_uniform_draws(vals, 0.0);
    std::vector<double> snd_normal_draws(vals, 0.0);

    // Simple random number generation method based on RAND
    // We could be more sophisticated an use a LCG or Mersenne Twister
    // but we're trying to demonstrate correlation, not efficient 
    // random number generation!
    for (int i = 0; i < snd_uniform_draws.size(); i++) {
        snd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
    }

    // Create standard normal random draws
    snd.random_draws(snd_uniform_draws, snd_normal_draws);

    /* CORRELATION SND */
    /* =============== */

    // Correlation coefficient
    double rho = 0.5;

    // Create the correlated standard normal distribution
    CorrelatedSND csnd(rho, &snd_normal_draws);
    std::vector<double> csnd_uniform_draws(vals, 0.0);
    std::vector<double> csnd_normal_draws(vals, 0.0);

    // Uniform generation for the correlated SND
    for (int i = 0; i < csnd_uniform_draws.size(); i++) {
        csnd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
    }

    // Now create the -correlated- standard normal draw series
    csnd.random_draws(csnd_uniform_draws, csnd_normal_draws);

    // Output the values of the standard normal random draws
    for (int i = 0; i < snd_normal_draws.size(); i++) {
        std::cout << snd_normal_draws[i] << ", " << csnd_normal_draws[i] << std::endl;
    }
}
