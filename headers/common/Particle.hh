#pragma once

#include <map>
#include <memory>

#include "kernel/Kernel.hh"
#include "kernel/KernelPoly6.hh"
#include "kernel/KernelSpiky.hh"
#include "kernel/KernelViscosity.hh"


#include "utils/Vec3.hh"
#include "common/Fluid.hh"
#include "Force.hh"

#define RAD_MUL = 2

struct Particle {
    Particle(double r, Fluid& flu, listForces& f, KernelPoly6& fKern,
             KernelSpiky& pKern,
             KernelViscosity& vKern,
             KernelPoly6& sKern, Vec3d pos, Vec3d spe, Vec3d acc);
    Particle(double r, Fluid& flu, listForces& f, KernelPoly6& fKern,
             KernelSpiky& pKern,
             KernelViscosity& vKern,
             KernelPoly6& sKern);
    
    void updateField(std::vector<std::shared_ptr<Particle>> neighb);
    void updateForce(std::vector<std::shared_ptr<Particle>> neighb);

    Fluid& flu; // réference vers un fluid
    KernelPoly6& fieldKernel;
    KernelSpiky& pressureKernel;
    KernelPoly6& surfaceKernel;
    KernelViscosity& viscosityKernel;

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
    Vec3d result_force;
    listForces ext_forces;

    Vec3d pressure_force;
    Vec3d viscosity_force;
    Vec3d surfaceTension_force;
};