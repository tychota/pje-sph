#pragma once

#include "kernel/Kernel.hh"
#include "utils/macros.hh"

class KernelBetaSpline : public Kernel {
public:
    KernelBetaSpline(double smoothingLength);
    KernelBetaSpline& operator=(const KernelBetaSpline& non) = delete;

    /** Calculates the kernel value at the given distance using a variable h value */
    virtual double W(double distance);

    /** Calculates the kernel derivative at the given distance using a variable h value */
    virtual Vec3d gradW(double distance, const Vec3d& distanceVector);

    /** Calculates the kernel laplacian at the given distance using a variable h value */
    virtual double laplacian(double distance, const Vec3d& distanceVector) const = 0;

    /** return the multiplier between smoothing length and max cutoff distance */
    virtual double getDilationFactor() const { return 2.0; }

    /** return the maximum distance at which this kernel is non zero */
    virtual double maxDistance() const = 0;

private:
    /** Normalization factor */
    double norme;

    /** Auxiliary factors for intermediate results: The inverse smoothing length */
    double reverseSmoothingLenght;

    /** Auxiliary factors for intermediate results: A pre-factor for w */
    double factorW;

    /** Auxiliary factors for intermediate results: A pre-factor for grad w */
    double factorGradW;
};

