#pragma once

#include "io/Writer.hpp"
#include "spdlog/details/format.h"

class TextWriter : public Writer {
    void write(vector<Particle>& partList, int step);
};

