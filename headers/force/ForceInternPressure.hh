#pragma once

#include "force/ForceIntern.hh"
#include "common/Particle.hh"

class ForceInternPressure : public ForceIntern {
  public:
    ForceInternPressure(shared_ptr<Kernel> kern);
    Vec3d F(Particle& part, std::vector<std::shared_ptr<Particle>> neigh);

  protected:
    double factor(Particle& part, std::shared_ptr<Particle> other);
};

