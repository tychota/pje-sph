#pragma once
#include <math.h>


class fluid {
public:
    fluid(double rho0, double b, double mu, double sigma, double k, double l, double cr);

    double rho0; // density at rest
    double b; // buoyancy
    double mu; // viscosity
    double sigma; // surface tension
    double k; // gaz shiffness
    double l; // threshold for normal computation
    double cr; // collision parameter
    double x;
};
