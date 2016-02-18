#include "io/TextWriter.hpp"

void TextWriter::write(const vector<shared_ptr<Particle>>& partList, int step) {
    ofstream mf;
    std::string filename = fmt::format("data{}.txt", step);
    mf.open(filename);

    mf << "PJE SPH step : " << step << endl;
    mf <<  endl;

    mf << "id" << "\t";

    mf << "pos x" << "\t";
    mf << "pos y" << "\t";
    mf << "pos z" << "\t";

    mf << "densi" << "\t";
    mf << "press" << "\t";

    mf << "col" << "\t";
    mf << "gcol n" << "\t";
    mf << "lcol" << "\t";

    mf << "spe x" << "\t";
    mf << "spe y" << "\t";
    mf << "spe z" << "\t";
    mf << "spe n" << "\t";

    mf << "acc x" << "\t";
    mf << "acc y" << "\t";
    mf << "acc z" << "\t";
    mf << "acc n" << "\t";

    mf << endl;
    for (auto part: partList) {
        mf << part->id << "\t";

        mf << part->curr_pos[0] << "\t";
        mf << part->curr_pos[1] << "\t";
        mf << part->curr_pos[2] << "\t";

        mf << part->density<< "\t";
        mf << part->pressure << "\t";

        mf << part->colour << "\t";
        mf << norm(part->colourDirection ) << "\t";
        mf << part->colourLaplacian << "\t";

        mf << part->curr_spe[0] << "\t";
        mf << part->curr_spe[1] << "\t";
        mf << part->curr_spe[2] << "\t";
        mf << norm(part->curr_spe) << "\t";

        mf << part->curr_acc[0] << "\t";
        mf << part->curr_acc[1] << "\t";
        mf << part->curr_acc[2] << "\t";
        mf << norm(part->curr_acc) << "\t";

        mf << endl;
    }

}
