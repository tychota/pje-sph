#pragma once

#include "io/Writer.hpp"
#include "spdlog/details/format.h"

class TextWriter : public Writer {
  public:
    TextWriter() {};
    void write(const vector<shared_ptr<Particle>>& partList, int step);
};

