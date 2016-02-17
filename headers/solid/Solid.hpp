#pragma once

#include "utils/macros.hpp"
#include "sph/Particle.hpp"

enum class SolidType {Obstacle, Recipient};

class Solid {
  public:
    Solid(double cr_co, SolidType type);

    virtual double implicitFunction(VEC pos) { throw NotImplementedException(); }

    virtual bool detect(VEC pos);
    void reaction(Particle& part, VEC pos_proj, double dist, VEC normal, double delta_t);

    virtual void react(Particle& part, double delta_t) { throw NotImplementedException(); }

  protected:
    double cr_co;
    SolidType type;
};

VEC tangentialIncoming(VEC incomming, VEC normal);

VEC rotateCoord(VEC v, VEC rotation);
