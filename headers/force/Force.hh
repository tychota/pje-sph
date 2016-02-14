#pragma once

#include <vector>
#include <memory>


#include "kernel/Kernel.hh"
#include "utils/Vec3.hh"

using namespace std;
class Force {
  public:
    Force();
};

typedef vector<shared_ptr<Force>> listForces;