#pragma once

#include <armadillo>
#include <vector>
#include <functional>

#include "io/Writer.hpp"
#include "io/TextWriter.hpp"
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

    void append(shared_ptr<Particle> part);

    void go();
    void step(bool initial);

    Box domain;
  private:
    TextWriter save;
    double smoothing;
    double delta_t;
    int number_frames;
    int steps_per_frame;

    vector<shared_ptr<Particle>> listPart;

    vector<Solid> listConstraints;
};

