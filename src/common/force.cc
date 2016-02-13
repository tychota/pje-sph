#include "common/force.hh"

Force::Force(std::function<Vec3d (Vec3d)> exp): exp(exp) { }

Vec3d Force::apply(Vec3d pos) {
    return exp(pos);
}
