#include <iostream>
#include <armadillo>


#include "sph/Solver.hpp"
#include "spdlog/spdlog.h"
#include "sph/Particle.hpp"
#include "solid/Box.hpp"


using namespace spdlog;
using namespace arma;

int main() {
    auto console = stdout_logger_mt("console");
    set_level(level::warn);

    VEC v0 = {0., 1., 0.};
    VEC vr = {0., 0., 0.};
    VEC v1 = {2., 2., 2.};
    Box b1(0.2, SolidType::Recipient, v0, vr, v1);
    Solver s(1, 50, 10, 10000, 0.1, b1);

    Fluid fluid1(1000, 0.1, 0.001, 0.2, 2, 0.1, 0.7);
    shared_ptr<Fluid> f1 = make_shared<Fluid>(fluid1);
    VEC g = {0, 0, -9.8};
    shared_ptr<Force> gravity = make_shared<Force>(g);
    listForces forces{gravity};
    shared_ptr<listForces> lf = make_shared<listForces>(forces);

    shared_ptr<KernelPoly6> kp6 = make_shared<KernelPoly6>(0.2);
    shared_ptr<KernelSpiky> ksp = make_shared<KernelSpiky>(0.2);
    shared_ptr<KernelViscosity> kv = make_shared<KernelViscosity>(0.2);

    Particle p1 = Particle(0.1, f1, lf, kp6, ksp, kv, kp6);

    s.append(p1);
}