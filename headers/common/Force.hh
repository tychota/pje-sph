#pragma once

#include <vector>
#include <memory>


#include "kernel/Kernel.hh"
#include "utils/Vec3.hh"

using namespace std;
class Force {
  public:
    Force(Vec3d dir);

    virtual Vec3d F();
    virtual Vec3d F(Vec3d Pos);
  protected:
    Vec3d val;
};

typedef vector<shared_ptr<Force>> listForces;