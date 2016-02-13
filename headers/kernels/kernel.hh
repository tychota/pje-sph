#pragma once

#include "utils/vec3.hh"

class Kernel {
public:
    Kernel(double smoothingLenght);
    virtual ~Kernel();

    /** Calculates the kernel value at the given distance. */
    virtual double call(double distance) const = 0;

    /** Calculates the kernel value at the given distance using a variable h value */
    virtual double call(double h, double distance) const = 0;

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

private:
    Kernel& operator=(const Kernel& non);
};

