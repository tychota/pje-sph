#include "solid/Solid.hpp"

Solid::Solid(double cr_co, SolidType type) : cr_co(cr_co), type(type) { }

bool Solid::detect(vec3 pos) {
    bool is_contain = (type == SolidType::Recipient);
    bool is_negat = (implicitFunction(pos) > 0);

    return (is_contain && not is_negat) || (not is_contain && is_negat);
}

void Solid::reaction(shared_ptr<Particle> part, vec3 pos_proj, double dist, vec3 normal, double delta_t) {
    vec3 spe = part->curr_spe;
    double cr = part->flu.cr;

    double distfactor = dist / (delta_t * norm(spe));

    vec3 surfaceSpeedReflection = - 2 * dot(spe, normal) * normal;
    vec3 surfaceSpeedAbsorbtion= (1 - cr * distfactor) * dot(spe, normal) * normal;
    vec3 surfaceSpeedFriction = - cr_co * distfactor * tangentialIncoming(spe, normal);

    spe = spe + surfaceSpeedAbsorbtion + surfaceSpeedReflection + surfaceSpeedFriction;

    part->reac_pos = pos_proj;
    part->curr_spe = spe;
}

vec3 tangentialIncoming(vec3 incomming, vec3 normal) {
    vec3 n = normalise(normal);
    vec3 d = normalise(incomming);

    if(dot(n, d) == 0.) {
        return d;
    }

    double k = 1.0;
    double l = - dot(n, n) / dot(n, d);

    return normalise(k * n + l * d);
}

vec3 rotateCoord(vec3 vec, vec3 rotation) {
    double cx = cos(rotation(0));
    double sx = sin(rotation(0));
    double cy = cos(rotation(1));
    double sy = sin(rotation(1));
    double cz = cos(rotation(2));
    double sz = sin(rotation(2));

    mat33 rotx = {{1, 0, 0}, {0, cx, -sx}, {0, sx, cx}};
    mat33 roty = {{cy, 0, -sy}, {0, 1, 0}, {sy, 0, cy}};
    mat33 rotz = {{cz, -sz, 0}, {sz, cz, 0}, {0, 0, 1}};


    mat33 rot = rotx * roty * rotz;
    return rot * vec;
};
