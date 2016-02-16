#include "solid/Box.hpp"


Box::Box(double cr_co, SolidType type, vec3 center, vec3 rotation, vec3 extendAxis) :
        Solid(cr_co, type),
        center(center),
        rotation(rotation),
        extendAxis(extendAxis) { }

vec3 Box::localCoord(vec3 globalCoord) {
    return rotateCoord(globalCoord - center, -rotation);
}

vec3 Box::globalCoord(vec3 localCoord) {
    return rotateCoord(localCoord, rotation) + center;
}

double Box::implicitFunction(vec3 pos) {
    vec3 pos_local = localCoord(pos);
    vec3 normalised_pos_local = {pos_local[0] / extendAxis[0],
                                 pos_local[1] / extendAxis[1],
                                 pos_local[2] / extendAxis[2]};
    return max(normalised_pos_local);
}

void Box::react(shared_ptr<Particle> part, double delta_t) {
    if (detect(part->next_pos)) {
        vec3 local_next_pos = localCoord(part->next_pos);
        vec3 intersec_loc = min(extendAxis, max(- extendAxis, local_next_pos));
        vec3 intersec_glob = globalCoord(intersec_loc);
        double dist = norm(intersec_glob - part->next_pos);
        vec3 intersec_normal = normalise(globalCoord(intersec_loc - local_next_pos));
        reaction(part, intersec_glob, dist, intersec_normal, delta_t);
    }
}
