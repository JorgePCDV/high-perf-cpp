#ifndef __FDM_H
#define __FDM_H

#include "pde.h"
#include <vector>

// Finite Difference Method - Abstract Base Class
class FDMBase {
protected:
    ConvectionDiffusionPDE* pde;

    // Space discretisation
    double x_dom;      // Spatial extent [0.0, x_dom]
    unsigned long J;   // Number of spatial differencing points
    double dx;         // Spatial step size (calculated from above)
    std::vector<double> x_values;  // Stores the coordinates of the x dimension

    // Time discretisation
    double t_dom;      // Temporal extent [0.0, t_dom]
    unsigned long N;   // Number of temporal differencing points
    double dt;         // Temporal step size (calculated from above)

    // Time-marching
    double prev_t, cur_t;

    // Differencing coefficients
    double alpha, beta, gamma;

    // Storage
    std::vector<double> new_result;
    std::vector<double> old_result;

    // Constructor
    FDMBase(double _x_dom, unsigned long _J,
        double _t_dom, unsigned long _N,
        ConvectionDiffusionPDE* _pde);

public:
    // Override these virtual methods in derived classes for 
    // specific FDM techniques, such as explicit Euler, Crank-Nicolson, etc.
    virtual void calculate_step_sizes() = 0;
    virtual void set_initial_conditions() = 0;
    virtual void calculate_boundary_conditions() = 0;
    virtual void calculate_inner_domain() = 0;
    virtual void step_march() = 0;
};

class FDMEulerExplicit : public FDMBase {
public:
    FDMEulerExplicit(double _x_dom, unsigned long _J,
        double _t_dom, unsigned long _N,
        ConvectionDiffusionPDE* _pde);

    void calculate_step_sizes();
    void set_initial_conditions();
    void calculate_boundary_conditions();
    void calculate_inner_domain();
    void step_march();
};

void FDMSolverExample();

#endif 
