#pragma once

#include "utils/Vec3.hh"
#include "common/Fluid.hh"
#include "force/Force.hh"

#define RAD_MUL = 2

class Particle {
public:
    Particle(double r, Fluid & flu, listForces& f, Vec3d pos, Vec3d spe, Vec3d acc);
    Particle(double r, Fluid & flu, listForces& f);

    Fluid& flu; // réference vers un fluid
    double rad; // rayon
    double mass; // masse de la particule
    double density;
    double pressure;

    // Position
    Vec3d curr_pos;
    Vec3d next_pos;
    Vec3d reac_pos;

    // Speed
    Vec3d curr_spe;
    Vec3d next_spe;
    Vec3d reac_spe;

    // Accélération
    Vec3d curr_acc;
    Vec3d next_acc;

    // Force
    listForces forces;
};

