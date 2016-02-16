#include <iostream>
#include <armadillo>

#include "spdlog/spdlog.h"
#include "common/Particle.hpp"
#include "structure/AccelerationMap.hpp"

using namespace spdlog;
using namespace arma;

int main() {
    auto console = stdout_logger_mt("console");
    set_level(level::warn);

    console->info("Bienvenu dans PJE SPH");

    mat A = randu<mat>(4,5);
    mat B = randu<mat>(4,5);

    cout << A*B.t() << endl;
}
