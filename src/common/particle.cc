#include "common/particle.hh"

Vec3d vn = Vec3d(0, 0, 0);

Particle::Particle(double r,
                   Fluid & flu,
                   listForces& f,
                   Vec3d pos,
                   Vec3d spe,
                   Vec3d acc):
        flu(flu),
        rad(r),
        forces(f)
{
    mass = (4. / 3. * PI * pow(rad, 3)) * flu.rho0; // sphérique
    
    curr_pos = Vec3d(pos.v[0], pos.v[1], pos.v[2]);
    next_pos = Vec3d(pos.v[0], pos.v[1], pos.v[2]);
    reac_pos = Vec3d(pos.v[0], pos.v[1], pos.v[2]);

    curr_spe = Vec3d(spe.v[0], spe.v[1], spe.v[2]);
    next_spe = Vec3d(spe.v[0], spe.v[1], spe.v[2]);
    reac_spe = Vec3d(spe.v[0], spe.v[1], spe.v[2]);

    curr_acc = Vec3d(mass*acc.v[0], mass*acc.v[1], mass*acc.v[2]);
    next_acc = Vec3d(mass*acc.v[0], mass*acc.v[1], mass*acc.v[2]);
}

Particle::Particle(double r, Fluid &flu, listForces& f) : Particle(r, flu, f, vn, vn, vn) { };