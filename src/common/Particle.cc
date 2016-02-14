#include "common/Particle.hh"

Vec3d vn = Vec3d(0, 0, 0);

Particle::Particle(double r,
                   Fluid & flu,
                   listForces& f,
                   shared_ptr<Kernel> mk,
                   Vec3d pos,
                   Vec3d spe,
                   Vec3d acc):
        flu(flu),
        rad(r),
        extForces(f),
        fieldKernel(mk)
{
    mass = (4. / 3. * PI * pow(rad, 3)) * flu.rho0; // sphérique

    colour = 0.;
    colourDirection = Vec3d(0, 0, 0);
    colourLaplacian = 0.;
    
    curr_pos = Vec3d(pos.v[0], pos.v[1], pos.v[2]);
    next_pos = Vec3d(pos.v[0], pos.v[1], pos.v[2]);
    reac_pos = Vec3d(pos.v[0], pos.v[1], pos.v[2]);

    curr_spe = Vec3d(spe.v[0], spe.v[1], spe.v[2]);
    next_spe = Vec3d(spe.v[0], spe.v[1], spe.v[2]);
    reac_spe = Vec3d(spe.v[0], spe.v[1], spe.v[2]);

    curr_acc = Vec3d(mass*acc.v[0], mass*acc.v[1], mass*acc.v[2]);
    next_acc = Vec3d(mass*acc.v[0], mass*acc.v[1], mass*acc.v[2]);
}

Particle::Particle(double r, Fluid &flu, listForces& f, shared_ptr<Kernel> mk) : Particle(r, flu, f, mk, vn, vn, vn) { };

void Particle::updateField(std::vector<std::shared_ptr<Particle>> neighb) {
    double dens = 0;
    double col = 0;
    double colLapl = 0;
    Vec3d colGrad = Vec3d();
    double colFactor = 0;
    double W;
    Vec3d dist;
    for (auto other: neighb) {
        dist = curr_pos - other->curr_pos;
        W = fieldKernel->W(dist);
        dens += other->mass * W;
        colFactor = other->mass / other->density;
        col += colFactor * W;
        colLapl += colFactor * fieldKernel->laplacianW(dist);
        colGrad += colFactor * fieldKernel->gradW(dist);
    }
    density =  dens;
    colour = col;
    colourDirection = colGrad;
    colourLaplacian = colLapl;
    pressure = (density - flu.rho0) * flu.k;
}

