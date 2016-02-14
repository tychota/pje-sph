#pragma once

#include "kernel/Kernel.hh"
#include "utils/macros.hh"

class KernelBox: public Kernel {
public:
    KernelBox(double smoothingLength);
    KernelBox& operator=(const KernelBox& non) = delete;

    virtual double W(double distance);
    virtual double W(Vec3d r){ return  W(r.len()); };

    virtual Vec3d gradW(double distance, const Vec3d& distanceVector);
    virtual Vec3d gradW(Vec3d r){ return  gradW(r.len(), r); };

    virtual double laplacian(double distance, const Vec3d& distanceVector);

    virtual double getDilationFactor() const { return 2.0; }
    virtual double maxDistance();

private:
    double scaleFactorW;
    double scaleFactorGradW;
    double reverseSmoothingLenght;
    double factorW;
    double factorGradW;

};

