#pragma once

#include "Solid.hpp"

class Cube : public Solid {
  public:
    Cube(double cr_co, Type type) : Solid(cr_co, type) { }
  private:
    vec3 center;
    vec3 rotation;
    vec3 extendAxis;
};
