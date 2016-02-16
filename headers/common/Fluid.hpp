/*!
* \file Fluid.hpp
* \brief Fluid parameter
* \author Tycho Tatitscheff
* \version 1.0
* \date 16 février 2017
*
* Define a structure containing all fluid parameters
 */

#include <math.h>


struct Fluid {
    Fluid(double rho0, double b, double mu, double sigma, double k, double l, double cr);

    double rho0; // density at rest
    double b; // buoyancy
    double mu; // viscosity
    double sigma; // surface tension
    double k; // gaz shiffness
    double l; // threshold for normal computation
    double cr; // collision parameter
    double x;
};
