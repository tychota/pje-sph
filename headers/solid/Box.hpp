#pragma once

#include "solid/Solid.hpp"

class Box : public Solid {
  public:
    Box(double cr_co, SolidType type, vec3 center, vec3 rotation, vec3 extendAxis);
    double implicitFunction(vec3 pos);
    vec3 localCoord(vec3 pos);
    vec3 globalCoord(vec3 localCoord);
    void react(shared_ptr<Particle> part, double delta_t);
  private:
    vec3 center;
    vec3 rotation;
    vec3 extendAxis;
};
