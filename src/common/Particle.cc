#include "common/Particle.hh"

Vec3d vn = Vec3d(0, 0, 0);

Particle::Particle(double r,
                   Fluid & flu,
                   listForces& f,
                   KernelPoly6& fKern,
                   KernelSpiky& pKern,
                   KernelViscosity& vKern,
                   KernelPoly6& sKern,
                   Vec3d pos,
                   Vec3d spe,
                   Vec3d acc):
        flu(flu),
        rad(r),
        ext_forces(f),
        fieldKernel(fKern),
        pressureKernel(pKern),
        viscosityKernel(vKern),
        surfaceKernel(sKern)

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

Particle::Particle(double r,
                   Fluid &flu,
                   listForces& f,
                   KernelPoly6& fKern,
                   KernelSpiky& pKern,
                   KernelViscosity& vKern,
                   KernelPoly6& sKern) : Particle(r, flu, f, fKern, pKern, vKern, sKern, vn, vn, vn) { };

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
        W = fieldKernel.W(dist);
        dens += other->mass * W;
        colFactor = other->mass / other->density;
        col += colFactor * W;
        colGrad += colFactor * fieldKernel.gradW(dist);
    }
    density =  dens;
    colour = col;
    colourDirection = colGrad;
    colourLaplacian = colLapl;
    pressure = (density - flu.rho0) * flu.k;
}

void Particle::updateForce(std::vector<std::shared_ptr<Particle>> neighb) {
    Vec3d dist;
    Vec3d tempPressureForce = Vec3d();
    Vec3d tempViscosityForce = Vec3d();
    Vec3d tempSurfaceTensionForce =  Vec3d();
    for (auto other: neighb) {
        dist = curr_pos - other->curr_pos;
        auto mj = mass;
        auto rho_j = density;
        auto rho_i = other->density;
        auto p_j = pressure;
        auto p_i = other->pressure;
        auto u_j = curr_spe;
        auto u_i = other->curr_spe;

        auto pressureFact = - mj * rho_j *  ((p_i + p_j) / ( 2 * rho_i * rho_j));
        auto viscosityVectFact = - mj * rho_j *  ((u_i + u_j) / ( 2 * rho_i * rho_j));

        tempPressureForce += pressureFact * pressureKernel.gradW(dist);
        tempViscosityForce += viscosityVectFact * pressureKernel.laplacianW(dist);
        if (colourDirection.len() <= flu.l) {
            tempSurfaceTensionForce -= flu.sigma * fieldKernel.laplacianW(dist) * fieldKernel.gradW(dist).normal();
        }
    }
    pressure_force =  tempPressureForce;
    viscosity_force = tempViscosityForce;
    surfaceTension_force = tempSurfaceTensionForce;

    result_force = tempPressureForce + tempViscosityForce + tempSurfaceTensionForce;
    for (auto f: ext_forces) {
        result_force += f->F(curr_pos);
    }
}
