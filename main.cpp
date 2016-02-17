#include <iostream>
#include <armadillo>

#include "spdlog/spdlog.h"
#include "common/Particle.hpp"
#include "structure/AccelerationMap.hpp"
#include "solid/Box.hpp"

using namespace spdlog;
using namespace arma;

int main() {
    auto console = stdout_logger_mt("console");
    set_level(level::warn);

    cout << sizeof(Particle) <<endl;
}
