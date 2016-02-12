#include <iostream>

#include "spdlog/spdlog.h"

#include "common/particle.hh"
#include "structure/proximityHash.hh"

namespace spd = spdlog;

using namespace std;
int main() {
    auto console = spd::stdout_logger_mt("console");
    spd::set_level(spd::level::debug);

    console->info("Bienvenu dans PJE SPH");
    proximityHash proximityHash1(12, 120);
}