#include "solid/Solid.hpp"

Solid::Solid(double cr_co, SolidType type) : cr_co(cr_co), type(type) { }

bool Solid::detect(VEC pos) {
    bool is_contain = (type == SolidType::Recipient);
    bool is_negat = (implicitFunction(pos) < 0);

    return (is_contain && not is_negat) || (not is_contain && is_negat);
}

void Solid::reaction(shared_ptr<Particle> part, VEC pos_proj, double dist, VEC normal, double delta_t) {
    VEC spe = part->next_spe;
    double cr = part->flu.cr;

    double distfactor = dist / (delta_t * norm(spe));

    VEC surfaceSpeedReflection = - 2 * dot(spe, normal) * normal;
    VEC surfaceSpeedAbsorbtion= (1 - cr * distfactor) * dot(spe, normal) * normal;
    VEC surfaceSpeedFriction = - cr_co * distfactor * tangentialIncoming(spe, normal);

    spe = spe + surfaceSpeedAbsorbtion + surfaceSpeedReflection + surfaceSpeedFriction;

    part->next_pos = pos_proj;
    part->next_spe = spe;
}

VEC tangentialIncoming(VEC incomming, VEC normal) {
    VEC n = normalise(normal);
    VEC d = normalise(incomming);

    if(dot(n, d) == 0.) {
        return d;
    }

    double k = 1.0;
    double l = - dot(n, n) / dot(n, d);

    return normalise(k * n + l * d);
}

VEC rotateCoord(VEC vect, VEC rotation) {
    double cx = cos(rotation(0));
    double sx = sin(rotation(0));
    double cy = cos(rotation(1));
    double sy = sin(rotation(1));
    double cz = cos(rotation(2));
    double sz = sin(rotation(2));

    mat rotx = {{1, 0, 0}, {0, cx, -sx}, {0, sx, cx}};
    mat roty = {{cy, 0, -sy}, {0, 1, 0}, {sy, 0, cy}};
    mat rotz = {{cz, -sz, 0}, {sz, cz, 0}, {0, 0, 1}};


    mat rot = rotx * roty * rotz;
    return rot * vect;
};
