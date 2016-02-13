#pragma once

#include "spdlog/spdlog.h"
namespace spd = spdlog;

#include "utils/Vec3.hh"
#include "exception/NotImplementedException.hh"

class Kernel {
public:
    Kernel(double smoothingLenght);;
    virtual ~Kernel()= 0;

    virtual double W(double distance);;
    virtual double W(double h, double distance);;

    virtual Vec3d gradW(double distance, const Vec3d& distanceVector);;
    virtual Vec3d gradW(double h, double distance, const Vec3d& distanceVector);;

    virtual double laplacian(double distance, const Vec3d& distanceVector);;
    virtual double laplacian(double h, double distance, const Vec3d& distanceVector);;

    virtual double getDilationFactor();

    virtual double maxDistance();;

protected:
    const double smoothingLength;
    std::shared_ptr<spdlog::logger> console = spd::get("console");

private:
    virtual Kernel& operator=(const Kernel& non) = 0;
};

