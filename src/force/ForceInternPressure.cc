#include "force/ForceInternPressure.hh"

ForceInternPressure::ForceInternPressure(shared_ptr<Kernel> kern) : ForceIntern(kern) { };

double ForceInternPressure::factor(Particle &part, std::shared_ptr<Particle> other) {
    auto mj = part.mass;
    auto rho_j = part.density;
    auto rho_i = other->density;
    auto p_j = part.pressure;
    auto p_i = other->pressure;

    return - mj * rho_j *  ((p_i + p_j) / ( 2* rho_i * rho_j));
}

Vec3d ForceInternPressure::F(Particle &part, std::vector<std::shared_ptr<Particle>> neigh) {
    return ForceIntern::F(part, neigh);
}
