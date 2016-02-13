#pragma once

#include "kernel/Kernel.hh"
#include "utils/macros.hh"

class KernelBetaSpline : public Kernel {
public:
    KernelBetaSpline(double smoothingLength);
    KernelBetaSpline& operator=(const KernelBetaSpline& non) = delete;

    /** Calculates the kernel value at the given distance using a variable h value */
    virtual double W(double distance);
    virtual double W(double h, double distance) const;

    /** Calculates the kernel derivative at the given distance using a variable h value */
    Vec3d gradiant(double distance, const Vec3d& distanceVector) const = 0;
    Vec3d gradiant(double h, double distance, const Vec3d& distanceVector) const = 0;

    /** Calculates the kernel laplacian at the given distance using a variable h value */
    virtual double laplacian(double distance, const Vec3d& distanceVector) const = 0;
    virtual double laplacian(double h, double distance, const Vec3d& distanceVector) const = 0;

    /** return the multiplier between smoothing length and max cutoff distance */
    virtual double getDilationFactor() const { return 2.0; }

    /** return the maximum distance at which this kernel is non zero */
    virtual double maxDistance() const = 0;

private:
    /** Normalization factor */
    double n;

    /** Auxiliary factors for intermediate results: The inverse smoothing length */
    double rH;

    /** Auxiliary factors for intermediate results: A pre-factor for w */
    double fW;

    /** Auxiliary factors for intermediate results: A pre-factor for grad w */
    double fGW;
};

