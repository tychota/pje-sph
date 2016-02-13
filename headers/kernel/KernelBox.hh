#pragma once

#include "kernel/Kernel.hh"
#include "utils/macros.hh"

class KernelBox: public Kernel {
public:
    KernelBox(double smoothingLength);
    KernelBox& operator=(const KernelBox& non) = delete;

    virtual double W(double distance);
    virtual Vec3d gradW(double distance, const Vec3d& distanceVector);

    /** Calculates the kernel laplacian at the given distance using a variable h value */
    virtual double laplacian(double distance, const Vec3d& distanceVector) const = 0;
    virtual double getDilationFactor() const { return 2.0; }
    virtual double maxDistance() const = 0;

private:
    double scaleFactorW;
    double scaleFactorGradW;
    double reverseSmoothingLenght;
    double factorW;
    double factorGradW;

};

