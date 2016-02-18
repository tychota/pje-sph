/*!
* \file Force.hpp
* \brief External force
* \author Tycho Tatitscheff
* \version 1.0
* \date 16 février 2017
*
* Define a Force class, that return the force vector for a given position vector
 */

#pragma once

#include <vector>
#include <memory>

#include "utils/macros.hpp"
#include "kernel/Kernel.hpp"

using namespace std;
class Force {
  public:
    Force(VEC dir);

    virtual VEC F();
    virtual VEC F(VEC Pos);
  protected:
    VEC val;
};

typedef vector<shared_ptr<Force>> listForces;
