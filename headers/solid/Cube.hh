#pragma once

#include "Solid.hh"

class Cube : public Solid {
  public:
    Cube(double cr_co, Type type) : Solid(cr_co, type) { }
  private:
    Vec3d center;
    Vec3d rotation;
    Vec3d extendAxis;
};

