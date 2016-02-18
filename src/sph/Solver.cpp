#include "sph/Solver.hpp"
Solver::Solver(double deltat_t,
               int number_frames,
               int steps_per_frame,
               int64_t number_particles,
               double smoothing,
               Box domain) :
        smoothing(smoothing),
        delta_t(deltat_t),
        number_frames(number_frames),
        steps_per_frame(steps_per_frame),
        domain(domain),
        save()
{ }

void Solver::addConstraint(Solid constraint) {
    listConstraints.push_back(constraint);
}

void Solver::append(shared_ptr<Particle> part) {
    listPart.push_back(part);
}


void Solver::go() {
    save.write(listPart, 0);
    step(true);
    for (int i = 1; i <= number_frames * steps_per_frame; i++) {
        if (i % steps_per_frame == 0) {
            save.write(listPart, i);
        }
        step(false);
    }
}

void Solver::step(bool initial) {
    for (auto &part: listPart) {
        double dens = 0;
        double col = 0;
        double colLapl = 0;
        VEC colGrad = {0, 0, 0};
        double colFactor = 0;
        double W;
        VEC dist;
        for (auto &other: listPart) {
            if (norm(part->curr_pos - other->curr_pos) < smoothing && !(*part == *other)) {
                dist = part->curr_pos - other->curr_pos;
                W = part->fieldKernel->W(dist);
                dens += other->mass * W;
                colFactor = other->mass / other->density;
                col += colFactor * W;
                colGrad += colFactor * part->fieldKernel->gradW(dist);
                colLapl += colFactor * part->fieldKernel->laplacianW(dist);
            }
        }
        part->density = dens;
        part->colour = col;
        part->colourDirection = colGrad;
        part->colourLaplacian = colLapl;
        part->pressure = (part->density - part->flu->rho0) * part->flu->k;
    }
    for (auto &part: listPart) {
        VEC dist;
        VEC tempPressureForce = {0., 0., 0.};
        VEC tempViscosityForce = {0., 0., 0.};
        VEC tempSurfaceTensionForce = {0., 0., 0.};
        for (auto &other: listPart) {
            if (norm(part->curr_pos - other->curr_pos) < smoothing && !(part == other)) {
                dist = part->curr_pos - other->curr_pos;
                auto mass_j = part->mass;
                auto rho_j = part->density;
                auto rho_i = other->density;
                auto pos_j = part->pressure;
                auto pos_i = other->pressure;
                auto spe_j = part->curr_spe;
                auto spe_i = other->curr_spe;

                auto pressureFact = -mass_j * rho_j * ((pos_i + pos_j) / (2 * rho_i * rho_j));
                auto viscosityVectFact = -mass_j * rho_j * ((spe_i + spe_j) / (2 * rho_i * rho_j));

                tempPressureForce += pressureFact * part->pressureKernel->gradW(dist);
                tempViscosityForce += viscosityVectFact * part->pressureKernel->laplacianW(dist);
                if (norm(part->colourDirection) <= part->flu->l) {
                    tempSurfaceTensionForce -= part->flu->sigma
                                               * part->fieldKernel->laplacianW(dist)
                                               * normalise(part->fieldKernel->gradW(dist));
                }
            }
        }
        part->pressure_force = tempPressureForce;
        part->viscosity_force = tempViscosityForce;
        part->surfaceTension_force = tempSurfaceTensionForce;

        part->result_force = tempPressureForce + tempViscosityForce + tempSurfaceTensionForce;
        for (auto f: *part->ext_forces) {
            part->result_force += f->F(part->curr_pos) * part->mass;
        }

        part->next_acc = part->result_force * 1. / part->mass;
        if (initial) {
            part->prev_half_spe = part->curr_spe;
        }
        part->next_half_spe = part->prev_half_spe + part->curr_acc * delta_t;
        part->curr_spe = 0.5 * (part->next_half_spe + part->prev_half_spe);
        part->next_pos = part->curr_pos + part->next_half_spe * delta_t;
    }
    for (auto &part: listPart) {
        for (auto f: listConstraints) {
            f.react(part, delta_t);
        }
        domain.react(part, delta_t);
        part->curr_acc = part->next_acc;
        part->prev_half_spe = part->next_half_spe;
        part->curr_spe = part->next_spe;
        part->curr_pos = part->next_pos;
    }
}

