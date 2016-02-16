#pragma once

#include "kernel/Kernel.hpp"
#include "utils/macros.hpp"

class KernelSine: public Kernel {
public:
    KernelSine(double smoothingLength);

    virtual double W(double distance);
    virtual double W(vec3 r){ return  W(norm(r)); };

    virtual vec3 gradW(double distance, const vec3& distanceVector);
    virtual vec3 gradW(vec3 r){ return  gradW(norm(r), r); };

    virtual double getDilationFactor() const { return 2.0; }
    virtual double maxDistance();

private:
    double norme;
    double factorW;
    double factorGradW;
};
