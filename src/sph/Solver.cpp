#include "sph/Solver.hpp"

Solver::Solver(double deltat_t,
               int number_frames,
               int steps_per_frame,
               int64_t number_particles,
               double part_radius,
               Box domain):
        delta_t(deltat_t),
        number_frames(number_frames),
        steps_per_frame(steps_per_frame),
        hashMap(part_radius, number_particles),
        domain(domain)
{ }

void Solver::addConstraint(Solid constraint) {
    listConstraints.push_back(constraint);
}

void Solver::append(Particle part) {
    hashMap.add(part);
    for (auto s: hashMap._map)
        for (auto& i : s.second)
            cout << &i << endl;
}
