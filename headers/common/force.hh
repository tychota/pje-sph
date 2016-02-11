#pragma once

#include <vector>
#include <functional>
#include <memory>

#include "utils/vec3.hh"

class force {
public:
    force(std::function<vec3d (vec3d)> exp);
    vec3d apply(vec3d pos);
private:
    std::function<vec3d (vec3d)> exp;
};

inline std::function<vec3d (vec3d)> uniform(vec3d dir) {
    return [dir](vec3d pos) {
        return dir;
    };
};

inline std::function<vec3d (vec3d)> unidir_square(vec3d orig, vec3d dir) {
    return [orig, dir](vec3d pos){
        return dir / pow((pos - orig).len2(), 2);
    };
};

typedef std::vector<std::shared_ptr<force>> listForces;