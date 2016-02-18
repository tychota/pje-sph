#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "exception/NotImplementedException.hpp"
#include "sph/Particle.hpp"

class Writer {
  public:
    Writer() {};
    virtual void write(const vector<shared_ptr<Particle>>& partList, int step);
};

