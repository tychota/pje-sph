/*!
* \file Particle.hpp
* \brief Particle structure
* \author Tycho Tatitscheff
* \version 1.0
* \date 16 février 2017
*
* Define a structure containing all field that a fluid particle may contain.
 */

#pragma once

#include <map>
#include <memory>
#include <vector>
#include <armadillo>

#include "kernel/Kernel.hpp"
#include "kernel/KernelPoly6.hpp"
#include "kernel/KernelSpiky.hpp"
#include "kernel/KernelViscosity.hpp"

#include "utils/Vec3.hpp"
#include "common/Fluid.hpp"
#include "Force.hpp"

using namespace arma;
using namespace std;

/**
 * \struct Particle
 * \brief Particle structure
 *
 * This structure contains all parameter carried by the fluid :
 *  - the position
 *  - the speed
 *  - the accelaration
 *  - the force applied
 *  - the mass
 *  - a pointer to the fluid
 */
struct Particle {
    Particle(double r, Fluid& flu, listForces& f, KernelPoly6& fKern,
             KernelSpiky& pKern,
             KernelViscosity& vKern,
             KernelPoly6& sKern,
             vec3 pos,
             vec3 spe,
             vec3 acc);
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
    vec3 colourDirection;

    // Position
    vec3 curr_pos;
    vec3 next_pos;
    vec3 reac_pos;

    // Speed
    vec3 curr_spe;
    vec3 next_spe;
    vec3 reac_spe;

    // Accélération
    vec3 curr_acc;
    vec3 next_acc;

    // Force
    vec3 result_force;
    listForces ext_forces;

    vec3 pressure_force;
    vec3 viscosity_force;
    vec3 surfaceTension_force;
};
