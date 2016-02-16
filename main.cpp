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
    vec3 v0 = {0., 0., 0.};
    vec3 v1 = {1., 1., 1.};
    Box b1(1, SolidType::Recipient, v0, v0, v1);

    Fluid fluid1(1000, 0.1, 0.001, 0.2, 2, 0.1, 0.7);
    vec3 g = {0, 0, -9.8};
    shared_ptr<Force> gravity = make_shared<Force>(g);
    listForces forces{gravity};
    KernelPoly6 kp6 = KernelPoly6(0.2);
    KernelSpiky ksp = KernelSpiky(0.2);
    KernelViscosity kv = KernelViscosity(0.2);
    shared_ptr<Particle> p1 = make_shared<Particle>(0.1, fluid1, forces, kp6, ksp, kv, kp6);

    p1->next_pos = {0., 0., 1.1};
    p1->next_pos = {1., -1., 1.1};

    b1.react(p1, 0.1);
}
