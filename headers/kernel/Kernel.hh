#pragma once

#include "spdlog/spdlog.h"
namespace spd = spdlog;

#include "utils/Vec3.hh"
#include "exception/NotImplementedException.hh"

class Kernel {
public:
    Kernel(double smoothingLenght);

    virtual double W(double distance);
    virtual double W(Vec3d r){ return  W(r.len()); };

    virtual Vec3d gradW(double distance, const Vec3d& distanceVector);
    virtual Vec3d gradW(Vec3d r){ return  gradW(r.len(), r); };

    virtual double laplacian(double distance, const Vec3d& distanceVector);

    virtual double getDilationFactor();

    virtual double maxDistance();

protected:
    const double smoothingLength;
    std::shared_ptr<spdlog::logger> console = spd::get("console");

};

