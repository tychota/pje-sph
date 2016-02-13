#include <iostream>

#include "spdlog/spdlog.h"

#include "common/Particle.hh"
#include "structure/AccelerationMap.hh"

namespace spd = spdlog;

using namespace std;
int main() {
    auto console = spd::stdout_logger_mt("console");
    spd::set_level(spd::level::debug);

    console->info("Bienvenu dans PJE SPH");
    AccelerationMap proximityHash1(12, 40000);
}