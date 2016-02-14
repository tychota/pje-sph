#pragma once

#include "force/ForceIntern.hh"
#include "common/Particle.hh"

class ForceInternSurfaceTension : public ForceIntern {
  public:
    ForceInternSurfaceTension(shared_ptr<Kernel> kern);
    Vec3d F(Particle& part, std::vector<std::shared_ptr<Particle>> neigh);

  protected:
    double factor(Particle& part, std::shared_ptr<Particle> other);
};

