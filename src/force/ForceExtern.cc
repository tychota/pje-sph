#include "force/ForceExtern.hh"


ForceExtern::ForceExtern(Vec3d dir) : val(dir) { }

Vec3d ForceExtern::F() {
    return val;
}

Vec3d ForceExtern::F(Particle &part, std::vector<std::shared_ptr<Particle>> neigh) {
    return F();
}
