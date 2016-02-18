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

#include "utils/macros.hpp"
#include "kernel/Kernel.hpp"
#include "kernel/KernelPoly6.hpp"
#include "kernel/KernelSpiky.hpp"
#include "kernel/KernelViscosity.hpp"

#include "common/Fluid.hpp"
#include "common/Force.hpp"

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
class Particle {
  public:
    Particle(double r,
             shared_ptr<Fluid> flu,
             shared_ptr<listForces> f,
             shared_ptr<KernelPoly6> fKern,
             shared_ptr<KernelSpiky> pKern,
             shared_ptr<KernelViscosity> vKern,
             shared_ptr<KernelPoly6> sKern,
             int id,
             VEC pos,
             VEC spe,
             VEC acc);
    Particle(double r,
             shared_ptr<Fluid> flu,
             shared_ptr<listForces> f,
             shared_ptr<KernelPoly6> fKern,
             shared_ptr<KernelSpiky> pKern,
             shared_ptr<KernelViscosity> vKern,
             shared_ptr<KernelPoly6> sKern,
             int id);

    void updateField(vector<shared_ptr<Particle>> neighb);
    void updateForce(vector<shared_ptr<Particle>> neighb);

    shared_ptr<Fluid> flu; // réference vers un fluid
    shared_ptr<KernelPoly6> fieldKernel;
    shared_ptr<KernelSpiky> pressureKernel;
    shared_ptr<KernelPoly6> surfaceKernel;
    shared_ptr<KernelViscosity> viscosityKernel;

    // Particule caracteristic
    double rad; // rayon
    double mass; // masse de la particule

    // Pressure related field
    double density;
    double pressure;

    // Colour field
    double colour;
    double colourLaplacian;
    VEC colourDirection;

    // Position
    VEC curr_pos;
    VEC next_pos;

    // Speed
    // prev_half and next_half are for leapfrog
    VEC prev_half_spe;
    VEC curr_spe;
    VEC next_half_spe;
    VEC next_spe;

    // Accélération
    VEC curr_acc;
    VEC next_acc;

    // Force
    VEC result_force;
    shared_ptr<listForces> ext_forces;

    VEC pressure_force;
    VEC viscosity_force;
    VEC surfaceTension_force;

    int id;
};

inline bool operator<(const Particle& lhs, const Particle& rhs) {
    return lhs.id < rhs.id;
}

inline bool operator==(const Particle& lhs, const Particle& rhs) {
    return lhs.id == rhs.id;
}