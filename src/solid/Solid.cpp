#include "solid/Solid.hpp"

Solid::Solid(double cr_co, Type type) : cr_co(cr_co), type(type) { }

bool Solid::detect(vec3 pos) {
    bool is_contain = (type == Type::Recipient);
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
