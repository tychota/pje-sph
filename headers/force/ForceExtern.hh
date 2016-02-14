#pragma once

#include "force/Force.hh"
#include "common/Particle.hh"

#include "kernel/Kernel.hh"
#include "utils/Vec3.hh"

using namespace std;
class ForceExtern : public Force {
  public:
    ForceExtern(Vec3d dir);

  protected:
    virtual Vec3d F();
    virtual Vec3d F(Particle& part, std::vector<std::shared_ptr<Particle>> neigh);
    Vec3d val;
};

typedef vector<shared_ptr<Force>> listForces;