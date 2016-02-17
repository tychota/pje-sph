#pragma once

#include <armadillo>
#include <vector>
#include <functional>

#include "solid/Solid.hpp"
#include "solid/Box.hpp"
#include "sph/Particle.hpp"

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

    void append(Particle& part);

    void go();
    void step(bool initial);

  private:
    double smoothing;
    double delta_t;
    int number_frames;
    int steps_per_frame;

    vector<Particle> listPart;

    Box domain;
    vector<Solid> listConstraints;
};

