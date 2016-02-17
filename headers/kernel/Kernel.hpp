#pragma once

#include <armadillo>
#include "utils/macros.hpp"
#include "spdlog/spdlog.h"
#include "exception/NotImplementedException.hpp"

using namespace spdlog;
using namespace arma;
using namespace std;

class Kernel {
public:
    Kernel(double smoothingLenght);

    virtual double W(double distance);
    virtual double W(VEC r){ return  W(norm(r)); };

    virtual VEC gradW(double distance, const VEC& distanceVector);
    virtual VEC gradW(VEC r){ return  gradW(norm(r), r); };

    virtual double laplacianW(double distance, const VEC &distanceVector);
    virtual double laplacianW(const VEC r){ return  laplacianW(norm(r), r); };

    virtual double maxDistance();

protected:
    double smoothingLength;
    shared_ptr<logger> console = get("console");

};

typedef map<const char*, Kernel> mapKernel;
