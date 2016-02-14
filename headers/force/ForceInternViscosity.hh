#pragma once

#include "force/ForceIntern.hh"
#include "common/Particle.hh"

class ForceInternViscosity : public ForceIntern {
  public:
    ForceInternViscosity(shared_ptr<Kernel> kern);
    Vec3d F(Particle& part, std::vector<std::shared_ptr<Particle>> neigh);

  protected:
    Vec3d factorV(Particle& part, std::shared_ptr<Particle> other);
};