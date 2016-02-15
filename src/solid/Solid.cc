#include "solid/Solid.hh"

Solid::Solid(double cr_co, Type type) : cr_co(cr_co), type(type) { }

bool Solid::detect(Vec3d pos) {
    bool is_contain = (type == Type::Recipient);
    bool is_negat = (implicitFunction(pos) > 0);

    return (is_contain && not is_negat) || (not is_contain && is_negat);
}

void Solid::reaction(shared_ptr<Particle> part, Vec3d pos_proj, double dist, Vec3d normal, double delta_t) {
    Vec3d spe = part->curr_spe;
    double cr = part->flu.cr;

    double distfactor = dist / (delta_t * spe.len());

    Vec3d surfaceSpeedReflection = - 2 * (spe * normal) * normal;
    Vec3d surfaceSpeedAbsorbtion= (1 - cr * distfactor) * (spe * normal) * normal;
    Vec3d surfaceSpeedFriction = - cr_co * distfactor * tangentialIncoming(spe, normal);

    spe = spe + surfaceSpeedAbsorbtion + surfaceSpeedReflection + surfaceSpeedFriction;

    part->reac_pos = pos_proj;
    part->curr_spe = spe;
}

Vec3d tangentialIncoming(Vec3d incomming, Vec3d normal) {
    Vec3d norm = normal.normal();
    Vec3d dir = (incomming).normal();

    if(norm * dir == 0.) {
        return dir;
    }

    double k = 1.0;
    double l = - (norm * norm) / (norm * dir);

    return (k * norm + l * dir).normal();
}
