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

    density = flu.rho0;
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
        dist = this->curr_pos - other->curr_pos;
        W = this->fieldKernel.W(dist);
        dens += other->mass * W;
        colFactor = other->mass / other->density;
        col += colFactor * W;
        colGrad += colFactor * this->fieldKernel.gradW(dist);
        colLapl += colFactor * this->fieldKernel.laplacianW(dist);
    }
    this->density =  dens;
    this->colour = col;
    this->colourDirection = colGrad;
    this->colourLaplacian = colLapl;
    this->pressure = (this->density - this->flu.rho0) * this->flu.k;
}

void Particle::updateForce(std::vector<std::shared_ptr<Particle>> neighb) {
    Vec3d dist;
    Vec3d tempPressureForce = Vec3d();
    Vec3d tempViscosityForce = Vec3d();
    Vec3d tempSurfaceTensionForce =  Vec3d();
    for (auto other: neighb) {
        dist = this->curr_pos - other->curr_pos;
        auto mass_j = this->mass;
        auto rho_j = this->density;
        auto rho_i = other->density;
        auto pos_j = this->pressure;
        auto pos_i = other->pressure;
        auto spe_j = this->curr_spe;
        auto spe_i = other->curr_spe;

        auto pressureFact = -mass_j * rho_j * ((pos_i + pos_j) / (2 * rho_i * rho_j));
        auto viscosityVectFact = -mass_j * rho_j * ((spe_i + spe_j) / (2 * rho_i * rho_j));

        tempPressureForce += pressureFact * this->pressureKernel.gradW(dist);
        tempViscosityForce += viscosityVectFact * this->pressureKernel.laplacianW(dist);
        if (this->colourDirection.len() <= this->flu.l) {
            tempSurfaceTensionForce -= this->flu.sigma
                                       * this->fieldKernel.laplacianW(dist)
                                       * this->fieldKernel.gradW(dist).normal();
        }
    }
    this->pressure_force =  tempPressureForce;
    this->viscosity_force = tempViscosityForce;
    this->surfaceTension_force = tempSurfaceTensionForce;

    this->result_force = tempPressureForce + tempViscosityForce + tempSurfaceTensionForce;
    for (auto f: this->ext_forces) {
        this->result_force += f->F(this->curr_pos) * this->mass;
    }
}
