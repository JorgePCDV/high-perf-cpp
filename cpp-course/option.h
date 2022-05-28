#ifndef __OPTION_H
#define __OPTION_H

#include "payoff.h"

class Option {
public:
    PayOff* pay_off;
    double K;
    double r;
    double T;

    Option(double _K, double _r,
        double _T, PayOff* _pay_off);

    virtual ~Option();
};

class VanillaOption {
public:
    PayOff* pay_off;

    double K;
    double r;
    double T;
    double sigma;

    VanillaOption();
    VanillaOption(double _K, double _r, double _T,
        double _sigma, PayOff* _pay_off);
};

#endif