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

    virtual double laplacianW(double distance, const Vec3d &distanceVector);
    virtual double laplacianW(const Vec3d r){ return  laplacianW(r.len(), r); };

    virtual double getDilationFactor();

    virtual double maxDistance();

protected:
    double smoothingLength;
    std::shared_ptr<spdlog::logger> console = spd::get("console");

};

typedef std::map<const char*, Kernel> mapKernel;