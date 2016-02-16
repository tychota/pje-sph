#include "common/Fluid.hpp"

Fluid::Fluid(double rho0, double b, double mu, double sigma, double k, double l, double cr)
        : rho0(rho0),
          b(b),
          mu(mu),
          sigma(sigma),
          k(k),
          l(l),
          cr(cr),
          x(floor(rho0 / pow(l, 2)))
{ }
