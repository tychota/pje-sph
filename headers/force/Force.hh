#pragma once

#include <vector>
#include <functional>
#include <memory>

#include "utils/Vec3.hh"

class Force {
public:
    Force(std::function<Vec3d (Vec3d)> exp);
    Vec3d apply(Vec3d pos);
private:
    std::function<Vec3d (Vec3d)> exp;
};

inline std::function<Vec3d (Vec3d)> uniform(Vec3d dir) {
    return [dir](Vec3d pos) {
        return dir;
    };
};

inline std::function<Vec3d (Vec3d)> unidir_square(Vec3d orig, Vec3d dir) {
    return [orig, dir](Vec3d pos){
        return dir / pow((pos - orig).len2(), 2);
    };
};

typedef std::vector<std::shared_ptr<Force>> listForces;