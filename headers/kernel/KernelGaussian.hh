#pragma once

#include "kernel/Kernel.hh"
#include "utils/macros.hh"

class KernelGaussian: public Kernel {
public:
    KernelGaussian(double smoothingLength);
    KernelGaussian& operator=(const KernelGaussian& non) = delete;

    virtual double W(double distance);
    virtual Vec3d gradW(double distance, const Vec3d& distanceVector);

    /** Calculates the kernel laplacian at the given distance using a variable h value */
    virtual double laplacian(double distance, const Vec3d& distanceVector) const = 0;
    virtual double getDilationFactor() const { return 2.0; }
    virtual double maxDistance();

private:
    double norme;
    double reverseSmoothingLenght;
    double factorW;
    double factorGradW;
};

