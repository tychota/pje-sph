#include <iostream>

#include "spdlog/spdlog.h"
namespace spd = spdlog;

#include "common/Particle.hh"
#include "structure/AccelerationMap.hh"



using namespace std;
int main() {
    auto console = spd::stdout_logger_mt("console");
    spd::set_level(spd::level::debug);

    console->info("Bienvenu dans PJE SPH");

}