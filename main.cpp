#include <iostream>

#include "spdlog/spdlog.h"
namespace spd = spdlog;

#include "common/Particle.hh"
#include "structure/AccelerationMap.hh"
#include "utils/Matrix.hh"



using namespace std;
int main() {
    auto console = spd::stdout_logger_mt("console");
    spd::set_level(spd::level::warn);

    console->info("Bienvenu dans PJE SPH");

    Matrix M(3, 3);
    M[0][0] = 4;
    cout << M << endl;
}