#pragma once

#include "force/Force.hh"
#include "common/Particle.hh"

#include "kernel/Kernel.hh"
#include "utils/Vec3.hh"

using namespace std;
class ForceIntern : public  Force {
  public:
    ForceIntern(shared_ptr<Kernel> kern);

  protected:
    virtual double factor(Particle& part, std::shared_ptr<Particle> other) = 0;
    virtual Vec3d F(Particle& part, std::vector<std::shared_ptr<Particle>> neigh);

    shared_ptr<Kernel> kern;
};

typedef vector<shared_ptr<Force>> listForces;