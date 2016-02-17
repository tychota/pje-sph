#pragma once

#include "utils/macros.hpp"
#include "common/Particle.hpp"

enum class SolidType {Obstacle, Recipient};


class Solid {
  public:
    Solid(double cr_co, SolidType type);
    virtual double implicitFunction(VEC pos) = 0;
    virtual bool detect(VEC pos);
    void reaction(shared_ptr<Particle> part, VEC pos_proj, double dist, VEC normal, double delta_t);
    virtual void react(shared_ptr<Particle> part, double delta_t) = 0;
  protected:
    double cr_co;
    SolidType type;
};

VEC tangentialIncoming(VEC incomming, VEC normal);

VEC rotateCoord(VEC v, VEC rotation);
