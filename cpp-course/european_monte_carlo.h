#pragma once

double gaussian_box_muller();
double monte_carlo_call_price(const int& num_sims, const double& S,
							  const double& K, const double& r,
							  const double& v, const double& T);
double monte_carlo_put_price(const int& num_sims, const double& S,
							  const double& K, const double& r,
							  const double& v, const double& T);

void EuropeanMonteCarlo();