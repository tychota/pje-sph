#include "common/particle.hh"

vec3d vn = vec3d(0, 0, 0);

particle::particle(double r,
                   fluid & flu,
                   listForces& f,
                   vec3d pos,
                   vec3d spe,
                   vec3d acc):
        flu(flu),
        rad(r),
        forces(f)
{
    mass = (4. / 3. * PI * pow(rad, 3)) * flu.rho0; // sphérique
    
    curr_pos = vec3d(pos.v[0], pos.v[1], pos.v[2]);
    next_pos = vec3d(pos.v[0], pos.v[1], pos.v[2]);
    reac_pos = vec3d(pos.v[0], pos.v[1], pos.v[2]);

    curr_spe = vec3d(spe.v[0], spe.v[1], spe.v[2]);
    next_spe = vec3d(spe.v[0], spe.v[1], spe.v[2]);
    reac_spe = vec3d(spe.v[0], spe.v[1], spe.v[2]);

    curr_acc = vec3d(mass*acc.v[0], mass*acc.v[1], mass*acc.v[2]);
    next_acc = vec3d(mass*acc.v[0], mass*acc.v[1], mass*acc.v[2]);
}

particle::particle(double r, fluid &flu, listForces& f) : particle(r, flu, f, vn, vn, vn) { };