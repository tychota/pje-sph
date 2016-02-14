#pragma once

#include "kernel/Kernel.hh"
#include "utils/macros.hh"

class KernelSplineS35 : public Kernel {
  public:
    KernelSplineS35(double smoothingLength);
    KernelSplineS35 & operator=(const KernelSplineS35 & non) = delete;

    virtual double W(double distance);
    virtual double W(Vec3d r){ return  W(r.len()); };

    virtual Vec3d gradW(double distance, const Vec3d& distanceVector);
    virtual Vec3d gradW(Vec3d r){ return  gradW(r.len(), r); };

    virtual double laplacian(double distance, const Vec3d& distanceVector);

    virtual double getDilationFactor() const { return 2.0; }
    virtual double maxDistance();

  private:
    double norme;
    double reverseSmoothingLenght;
    double factorW;
    double factorGradW;
};
