#pragma once

#include "utils/vec3.hh"
#include "common/fluid.hh"
#include "common/force.hh"

#define RAD_MUL = 2

class particle {
public:
    particle(double r, fluid & flu, listForces& f, vec3d pos, vec3d spe, vec3d acc);
    particle(double r, fluid & flu, listForces& f);

    fluid& flu; // réference vers un fluid
    double rad; // rayon
    double mass; // masse de la particule
    double density;
    double pressure;

    // Position
    vec3d curr_pos;
    vec3d next_pos;
    vec3d reac_pos;

    // Speed
    vec3d curr_spe;
    vec3d next_spe;
    vec3d reac_spe;

    // Accélération
    vec3d curr_acc;
    vec3d next_acc;

    // Force
    listForces forces;
};

