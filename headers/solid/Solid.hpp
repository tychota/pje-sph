#pragma once

#include "common/Particle.hpp"
#include "utils/Vec3.hpp"

enum class SolidType {Obstacle, Recipient};


class Solid {
  public:
    Solid(double cr_co, SolidType type);
    virtual double implicitFunction(vec3 pos) = 0;
    virtual bool detect(vec3 pos);
    void reaction(shared_ptr<Particle> part, vec3 pos_proj, double dist, vec3 normal, double delta_t);
    virtual void react(shared_ptr<Particle> part, double delta_t) = 0;
  protected:
    double cr_co;
    SolidType type;
};

vec3 tangentialIncoming(vec3 incomming, vec3 normal);

vec3 rotateCoord(vec3 vec, vec3 rotation);
