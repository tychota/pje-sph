#include "solid/Box.hpp"


Box::Box(double cr_co, SolidType type, VEC center, VEC rotation, VEC extendAxis) :
        Solid(cr_co, type),
        center(center),
        rotation(rotation),
        extendAxis(extendAxis) { }

VEC Box::localCoord(VEC globalCoord) {
    VEC local = rotateCoord(globalCoord - center, -rotation);
    return local;
}

VEC Box::globalCoord(VEC localCoord) {
    VEC global = rotateCoord(localCoord, rotation) + center;
    return global;
}

double Box::implicitFunction(VEC pos) {
    VEC diff_pos_local = sqrt(square(localCoord(pos))) - extendAxis;
    double implicit = max(diff_pos_local);
    return implicit;
}

void Box::react(Particle& part, double delta_t) {
    if (detect(part.next_pos)) {
        VEC local_next_pos = localCoord(part.next_pos);
        VEC intersec_loc = min(extendAxis, max(- extendAxis, local_next_pos));
        VEC intersec_glob = globalCoord(intersec_loc);
        double dist = norm(intersec_glob - part.next_pos);
        VEC intersec_normal = normalise(globalCoord(local_next_pos - intersec_loc));
        reaction(part, intersec_glob, dist, intersec_normal, delta_t);
    }
}
