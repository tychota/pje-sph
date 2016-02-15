#pragma once

#include "common/Particle.hh"
#include "utils/Vec3.hh"

enum class Type {Obstacle, Recipient};


class Solid {
  public:
    Solid(double cr_co, Type type);
    virtual double implicitFunction(Vec3d pos) = 0;
    virtual bool detect(Vec3d pos);
    void reaction(shared_ptr<Particle> part, Vec3d pos_proj, double dist, Vec3d normal, double delta_t);
    virtual void react(shared_ptr<Particle> part, double delta_t) = 0;
  private:
    double cr_co;
    Type type;
};

Vec3d tangentialIncoming(Vec3d incomming, Vec3d normal);