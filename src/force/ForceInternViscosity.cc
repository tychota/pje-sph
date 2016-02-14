#include "force/ForceInternViscosity.hh"

ForceInternViscosity::ForceInternViscosity(shared_ptr<Kernel> kern) : ForceIntern(kern) { };

Vec3d ForceInternViscosity::factorV(Particle &part, std::shared_ptr<Particle> other) {
    auto mj = part.mass;
    auto rho_j = part.density;
    auto rho_i = other->density;
    auto u_j = part.curr_spe;
    auto u_i = other->curr_spe;

    return - mj * rho_j *  ((u_i + u_j) / ( 2* rho_i * rho_j));
}

Vec3d ForceInternViscosity::F(Particle &part, std::vector<std::shared_ptr<Particle>> neigh) {
    Vec3d resultant = Vec3d();
    for (auto other: neigh) {
        Vec3d dist = part.curr_pos - other->curr_pos;
        auto fac = factorV(part, other);
        auto ker = kern->laplacianW(dist);
        resultant += fac * ker;
    }
    return resultant;
}