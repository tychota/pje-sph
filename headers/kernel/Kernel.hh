#pragma once

#include "spdlog/spdlog.h"
namespace spd = spdlog;

#include "utils/Vec3.hh"


class Kernel {
public:
    Kernel(double smoothingLenght);
    virtual ~Kernel();

    /** Calculates the kernel value at the given distance. */
    virtual double W(double distance) const = 0;
    virtual double W(double h, double distance) const = 0;

    /** Calculates the kernel derivative at the given distance using a variable h value */
    virtual Vec3d gradiant(double distance, const Vec3d& distanceVector) const = 0;
    virtual Vec3d gradiant(double h, double distance, const Vec3d& distanceVector) const = 0;

    /** Calculates the kernel laplacian at the given distance using a variable h value */
    virtual double laplacian(double distance, const Vec3d& distanceVector) const = 0;
    virtual double laplacian(double h, double distance, const Vec3d& distanceVector) const = 0;

    /** return the multiplier between smoothing length and max cutoff distance */
    virtual double getDilationFactor() const { return 2.0; }

    /** return the maximum distance at which this kernel is non zero */
    virtual double maxDistance() const = 0;

protected:
    const double smoothingLength;
    std::shared_ptr<spdlog::logger> console = spd::get("console");

private:
    Kernel& operator=(const Kernel& non);
};

