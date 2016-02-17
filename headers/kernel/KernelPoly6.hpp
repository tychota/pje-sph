#pragma once

#include "kernel/Kernel.hpp"
#include "utils/macros.hpp"

class KernelPoly6: public Kernel {
public:
    KernelPoly6(double smoothingLength);

    virtual double W(double distance);
    virtual double W(VEC r){ return  W(norm(r)); };

    virtual VEC gradW(double distance, const VEC& distanceVector);
    virtual VEC gradW(VEC r){ return  gradW(norm(r), r); };

    virtual double laplacianW(double distance, const VEC &distanceVector);
    virtual double laplacianW(const VEC r){ return  laplacianW(norm(r), r); };

    virtual double maxDistance();

private:
    double norme;
    double factorW;
    double factorGradW;
    double factorLapW;
};
