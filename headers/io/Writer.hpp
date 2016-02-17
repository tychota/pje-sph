#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "exception/NotImplementedException.hpp"
#include "sph/Particle.hpp"

class Writer {
    virtual void write(vector<Particle>& partList, int step);
};

