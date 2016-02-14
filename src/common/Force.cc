#include "common/Force.hh"

Force::Force(Vec3d dir) : val(dir) { }

Vec3d Force::F() {
    return val;
}

Vec3d Force::F(Vec3d pos) {
    return F();
}
