#pragma once

#include "Solid.hpp"

class Box : public Solid {
  public:
    Box(double cr_co, Type type);
  private:
    vec3 center;
    vec3 rotation;
    vec3 extendAxis;
};
