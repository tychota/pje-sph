#pragma once

#include "solid/Solid.hpp"

class Box : public Solid {
  public:
    Box(double cr_co, SolidType type, VEC center, VEC rotation, VEC extendAxis);
    double implicitFunction(VEC pos);
    VEC localCoord(VEC pos);
    VEC globalCoord(VEC localCoord);
    VEC localRange() {return extendAxis;};
    void react(shared_ptr<Particle> part, double delta_t);
  private:
    VEC center;
    VEC rotation;
    VEC extendAxis;
};
