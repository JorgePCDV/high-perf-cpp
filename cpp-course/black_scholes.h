#pragma once

double norm_pdf(const double x);
double norm_cdf(const double x);
double d_j(const int j, const double S, const double K, const double r, const double v, const double T);
double call_price(const double S, const double K, const double r, const double v, const double T);
double call_delta(const double S, const double K, const double r, const double v, const double T);
double call_gamma(const double S, const double K, const double r, const double v, const double T);
double call_vega(const double S, const double K, const double r, const double v, const double T);
double call_theta(const double S, const double K, const double r, const double v, const double T);
double call_rho(const double S, const double K, const double r, const double v, const double T);

double put_price(const double S, const double K, const double r, const double v, const double T);
double put_delta(const double S, const double K, const double r, const double v, const double T);
double put_gamma(const double S, const double K, const double r, const double v, const double T);
double put_vega(const double S, const double K, const double r, const double v, const double T);
double put_theta(const double S, const double K, const double r, const double v, const double T);
double put_rho(const double S, const double K, const double r, const double v, const double T);

double call_delta_fdm(const double S, const double K, const double r, const double v, const double T, const double delta_S);
double call_gamma_fdm(const double S, const double K, const double r, const double v, const double T, const double delta_S);

void monte_carlo_call_price(const int num_sims,
    const double S, const double K, const double r,
    const double v, const double T, const double delta_S,
    double& price_Sp, double& price_S, double& price_Sm);
double call_delta_mc(const int num_sims, const double S, const double K, const double r, const double v, const double T, const double delta_S);
double call_gamma_mc(const int num_sims, const double S, const double K, const double r, const double v, const double T, const double delta_S);



void GreeksAnalyticExample();
void GreeksFiniteDifferenceMethod();
void GreeksMonteCarloExample();