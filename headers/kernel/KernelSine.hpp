#pragma once

#include "kernel/Kernel.hpp"
#include "utils/macros.hpp"

class KernelSine: public Kernel {
public:
    KernelSine(double smoothingLength);

    virtual double W(double distance);
    virtual double W(VEC r){ return  W(norm(r)); };

    virtual VEC gradW(double distance, const VEC& distanceVector);
    virtual VEC gradW(VEC r){ return  gradW(norm(r), r); };

    virtual double maxDistance();

private:
    double norme;
    double factorW;
    double factorGradW;
};
