#include "common/Fluid.hpp"

Fluid::Fluid(double rho0, double mu, double sigma, double k, double l, double cr)
        : rho0(rho0),
          mu(mu),
          sigma(sigma),
          k(k),
          l(l),
          cr(cr)
{ }
