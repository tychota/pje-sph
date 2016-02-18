#include "io/TextWriter.hpp"

void TextWriter::write(vector<Particle> &partList, int step) {
    ofstream mf;
    std::string filename = fmt::format("data{}.txt", step);
    mf.open(filename);

    mf << "PJE SPH step : " << step << endl;
    mf <<  endl;

    mf << "pos x" << "\t";
    mf << "pos y" << "\t";
    mf << "pos z" << "\t";

    mf << "density" << "\t";
    mf << "pressure" << "\t";

    mf << "col" << "\t";
    mf << "g col x" << "\t";
    mf << "g col y" << "\t";
    mf << "g col z" << "\t";
    mf << "g col n" << "\t";
    mf << "lap col" << "\t";

    mf << "spe x" << "\t";
    mf << "spe y" << "\t";
    mf << "spe z" << "\t";
    mf << "spe n" << "\t";

    mf << "acc x" << "\t";
    mf << "acc y" << "\t";
    mf << "acc z" << "\t";
    mf << "acc n" << "\t";

    mf << "for pres x" << "\t";
    mf << "for pres y" << "\t";
    mf << "for pres z" << "\t";
    mf << "for pres n" << "\t";

    mf << "for visc x" << "\t";
    mf << "for visc y" << "\t";
    mf << "for visc z" << "\t";
    mf << "for visc n" << "\t";

    mf << "for surf x" << "\t";
    mf << "for surf y" << "\t";
    mf << "for surf z" << "\t";
    mf << "for surf n" << "\t";

    mf << "for res x" << "\t";
    mf << "for res y" << "\t";
    mf << "for res z" << "\t";
    mf << "for res n" << "\t";

    mf << endl;

    for (auto& part: partList) {
        mf << part.curr_pos[0] << "\t";
        mf << part.curr_pos[1] << "\t";
        mf << part.curr_pos[2] << "\t";
        
        mf << part.density<< "\t";
        mf << part.pressure << "\t";

        mf << part.colour << "\t";
        mf << part.colourDirection[0] << "\t";
        mf << part.colourDirection[0] << "\t";
        mf << part.colourDirection[0] << "\t";
        mf << norm( part.colourDirection ) << "\t";
        mf << part.colourLaplacian << "\t";

        mf << part.curr_spe[0] << "\t";
        mf << part.curr_spe[1] << "\t";
        mf << part.curr_spe[2] << "\t";
        mf << norm(part.curr_spe) << "\t";

        mf << part.curr_acc[0] << "\t";
        mf << part.curr_acc[1] << "\t";
        mf << part.curr_acc[2] << "\t";
        mf << norm(part.curr_acc) << "\t";

        mf << part.pressure_force[0] << "\t";
        mf << part.pressure_force[1] << "\t";
        mf << part.pressure_force[2] << "\t";
        mf << norm(part.pressure_force) << "\t";

        mf << part.viscosity_force[0] << "\t";
        mf << part.viscosity_force[1] << "\t";
        mf << part.viscosity_force[2] << "\t";
        mf << norm(part.viscosity_force) << "\t";

        mf << part.surfaceTension_force[0] << "\t";
        mf << part.surfaceTension_force[1] << "\t";
        mf << part.surfaceTension_force[2] << "\t";
        mf << norm(part.surfaceTension_force) << "\t";

        mf << part.result_force[0] << "\t";
        mf << part.result_force[1] << "\t";
        mf << part.result_force[2] << "\t";
        mf << norm(part.result_force) << "\t";

        mf << endl;
    }

}
