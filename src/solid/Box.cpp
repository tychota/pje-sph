#include "solid/Box.hpp"


Box::Box(double cr_co, SolidType type, VEC center, VEC rotation, VEC extendAxis) :
        Solid(cr_co, type),
        center(center),
        rotation(rotation),
        extendAxis(extendAxis) { }

VEC Box::localCoord(VEC globalCoord) {
    return rotateCoord(globalCoord - center, -rotation);
}

VEC Box::globalCoord(VEC localCoord) {
    return rotateCoord(localCoord, rotation) + center;
}

double Box::implicitFunction(VEC pos) {
    VEC diff_pos_local = sqrt(square(localCoord(pos))) - extendAxis;
    double implicit = max(diff_pos_local);
    return implicit;
}

void Box::react(shared_ptr<Particle> part, double delta_t) {
    if (detect(part->next_pos)) {
        VEC local_next_pos = localCoord(part->next_pos);
        cout << local_next_pos << endl;
        VEC intersec_loc = min(extendAxis, max(- extendAxis, local_next_pos));
        cout << intersec_loc << endl;
        VEC intersec_glob = globalCoord(intersec_loc);
        cout << intersec_glob << endl;
        double dist = norm(intersec_glob - part->next_pos);
        cout << dist << endl;
        VEC intersec_normal = normalise(globalCoord(local_next_pos - intersec_loc));
        cout << intersec_normal << endl;
        reaction(part, intersec_glob, dist, intersec_normal, delta_t);
    }
}
