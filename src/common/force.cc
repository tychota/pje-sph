#include "common/force.hh"

force::force(std::function<vec3d (vec3d)> exp): exp(exp) { }

vec3d force::apply(vec3d pos) {
    return exp(pos);
}
