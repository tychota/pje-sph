#include "common/Particle.hpp"

vec vn = zeros<vec>(3);

Particle::Particle(double r,
                   Fluid & flu,
                   listForces& f,
                   KernelPoly6& fKern,
                   KernelSpiky& pKern,
                   KernelViscosity& vKern,
                   KernelPoly6& sKern,
                   vec pos,
                   vec spe,
                   vec acc):
        flu(flu),
        rad(r),
        ext_forces(f),
        fieldKernel(fKern),
        pressureKernel(pKern),
        viscosityKernel(vKern),
        surfaceKernel(sKern),
        curr_pos(pos),
        next_pos(pos),
        reac_pos(pos),
        curr_spe(spe),
        next_spe(spe),
        reac_spe(spe),
        curr_acc(acc),
        next_acc(acc),
        colourDirection(vn)

{
    mass = (4. / 3. * PI * pow(rad, 3)) * flu.rho0; // sphérique

    colour = 0.;
    colourLaplacian = 0.;

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
    vec colGrad(3);
    colGrad.zeros();
    double colFactor = 0;
    double W;
    vec3 dist;
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
    vec3 dist;
    vec3 tempPressureForce = zeros<vec>(3);
    vec3 tempViscosityForce = zeros<vec>(3);
    vec3 tempSurfaceTensionForce = zeros<vec>(3);

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
        if (norm(this->colourDirection) <= this->flu.l) {
            tempSurfaceTensionForce -= this->flu.sigma
                                       * this->fieldKernel.laplacianW(dist)
                                       * normalise(this->fieldKernel.gradW(dist));
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
