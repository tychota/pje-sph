#pragma once

#include <armadillo>
#include <vector>
#include <functional>

#include "solid/Solid.hpp"
#include "solid/Box.hpp"
#include "sph/Particle.hpp"
#include "structure/AccelerationMap.hpp"

using namespace arma;
using namespace std;

class Solver {
  public:
    Solver(double deltat_t,
           int number_frames,
           int steps_per_frame,
           int64_t number_particles,
           double part_radius,
           Box domain);

    void addConstraint(Solid constraint);

    void append(Particle part);
    void fill(function<bool(VEC)>, Particle part_pattern);

    void go();
    void step();

    void updateField(shared_ptr<Particle>part);
    void updateForce(shared_ptr<Particle>part);
    void reactCollision(shared_ptr<Particle>part);

  private:
    double delta_t;
    int number_frames;
    int steps_per_frame;

    AccelerationMap hashMap;

    Box domain;
    vector<Solid> listConstraints;
};

