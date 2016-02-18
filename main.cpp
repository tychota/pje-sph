#include <iostream>
#include <armadillo>


#include "sph/Solver.hpp"
#include "spdlog/spdlog.h"
#include "sph/Particle.hpp"
#include "solid/Box.hpp"


using namespace spdlog;
using namespace arma;

void gen_fluid(Solver& s, Particle& po) {
    auto r = po.rad;
    auto l = s.getDomainRange();
    int id = 0;
    VEC debut = -l + VEC{r, r, r };
    VEC end = l - VEC{r, r, l[0] };
    for (double i = debut[0]; i <= end[0]; i+=2*r) {
        for (double j = debut[1]; j <= end[1]; j+=2*r) {
            for (double k = debut[2]; k <= end[2]; k+=2*r) {
                id ++;
                Particle p(po);
                p.curr_pos = VEC({i, j, k});
                p.id = id;
                s.append(make_shared<Particle>(p));
            }
        }
    }
}

int main() {
    auto console = stdout_logger_mt("console");
    set_level(level::info);

    VEC v0 = {0., 1., 0.};
    VEC vr = {0., 0., 0.};
    VEC v1 = {1., 1., 1.};
    Box b1(0.2, SolidType::Recipient, v0, vr, v1);

    Solver s(0.001, 50, 1, 0.3, b1);

    shared_ptr<Fluid> f1 = make_shared<Fluid>(1000, 0.001, 75.64, 2, 0.1, 0.7);
    shared_ptr<listForces> lf = make_shared<listForces>(listForces{make_shared<Force>(VEC{0, 0, -9.8})});

    shared_ptr<KernelPoly6> kp6 = make_shared<KernelPoly6>(0.3);
    shared_ptr<KernelSpiky> ksp = make_shared<KernelSpiky>(0.3);
    shared_ptr<KernelViscosity> kv = make_shared<KernelViscosity>(0.3);

    Particle p1 = Particle(0.05, f1, lf, kp6, ksp, kv, kp6, 0);

    gen_fluid(s, p1);

    s.go();
}

