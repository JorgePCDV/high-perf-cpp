#ifndef __OPTION_CPP
#define __OPTION_CPP

#include "option.h"

Option::Option(double _K, double _r,
	double _T, PayOff* _pay_off) :
	K(_K), r(_r), T(_T), pay_off(_pay_off) {}

Option::~Option() {}

VanillaOptionV2::VanillaOptionV2() {}

VanillaOptionV2::VanillaOptionV2(double _K, double _r, double _T,
	double _sigma, PayOff* _pay_off) :
	K(_K), r(_r), T(_T), sigma(_sigma), pay_off(_pay_off) {}

#endif