#pragma once

#include <armadillo>
#include "spdlog/spdlog.h"
#include "exception/NotImplementedException.hpp"

using namespace spdlog;
using namespace arma;
using namespace std;

class Kernel {
public:
    Kernel(double smoothingLenght);

    virtual double W(double distance);
    virtual double W(vec3 r){ return  W(norm(r)); };

    virtual vec3 gradW(double distance, const vec3& distanceVector);
    virtual vec3 gradW(vec3 r){ return  gradW(norm(r), r); };

    virtual double laplacianW(double distance, const vec3 &distanceVector);
    virtual double laplacianW(const vec3 r){ return  laplacianW(norm(r), r); };

    virtual double getDilationFactor();

    virtual double maxDistance();

protected:
    double smoothingLength;
    shared_ptr<logger> console = get("console");

};

typedef map<const char*, Kernel> mapKernel;
