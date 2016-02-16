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


#include "kernel/Kernel.hpp"
#include "utils/Vec3.hpp"

using namespace std;
class Force {
  public:
    Force(vec3 dir);

    virtual vec3 F();
    virtual vec3 F(vec3 Pos);
  protected:
    vec3 val;
};

typedef vector<shared_ptr<Force>> listForces;
