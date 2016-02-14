#pragma once

#include <map>
#include <memory>

#include "kernel/Kernel.hh"
#include <kernel/KernelPoly6.hh>

#include "utils/Vec3.hh"
#include "common/Fluid.hh"
#include "force/Force.hh"

#define RAD_MUL = 2

class Particle {
public:
    Particle(double r, Fluid& flu, listForces& f, shared_ptr<Kernel> kern, Vec3d pos, Vec3d spe, Vec3d acc);
    Particle(double r, Fluid& flu, listForces& f, shared_ptr<Kernel> kern);


    void updateField(std::vector<std::shared_ptr<Particle>> neighb);

    Fluid& flu; // réference vers un fluid
    shared_ptr<Kernel> fieldKernel;

    // Particule caracteristic
    double rad; // rayon
    double mass; // masse de la particule

    // Pressure related field
    double density;
    double pressure;

    // Colour field
    double colour;
    double colourLaplacian;
    Vec3d colourDirection;

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
    listForces extForces;
    Force pressureForce;
    Force viscosityForce;

};