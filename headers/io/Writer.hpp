#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "exception/NotImplementedException.hpp"
#include "sph/Particle.hpp"

#include "spdlog/spdlog.h"
using namespace spdlog;

class Writer {
  public:
    Writer() {};
    virtual void write(const vector<shared_ptr<Particle>>& partList, int step);

  protected:
    shared_ptr<logger> console = get("console");
};

