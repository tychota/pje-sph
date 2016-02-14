#include "force/ForceIntern.hh"

ForceIntern::ForceIntern(shared_ptr<Kernel> kern) : Force() { }

Vec3d ForceIntern::F(Particle &part, std::vector<std::shared_ptr<Particle>> neigh) {
    Vec3d resultant = Vec3d();
    for (auto other: neigh) {
        Vec3d dist = part.curr_pos - other->curr_pos;
        auto fac = factor(part, other);
        auto ker = kern->gradW(dist);
        resultant += fac * ker;
    }
    return resultant;
}
