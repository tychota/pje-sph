#include <iostream>


#include "common/particle.hh"
#include "common/fluid.hh"
#include "common/force.hh"
#include "structure/proximityHash.hh"
#include "utils/vec3.hh"


using namespace std;
int main() {
    prime prim;
    proximityHash prox(.1, 30);
    fluid fluid1(1, 2, 3, 4, 5, 6, 7);
    shared_ptr<force> grav = make_shared<force>(uniform(vec3d(0, 0, -9.8)));
    shared_ptr<force> f1 = make_shared<force>(unidir_square(vec3d(0, 0, 0), vec3d(0, 0, -9.8)));
    listForces force1 = {grav, f1};
    vec3d v1(1., 2., 3.);
    vec3d v2(-1., -2., -3.);
    vec3d v3(4., 5., 6.);
    vec3d v4(0, 0, 0);
    prox.add(make_shared<particle>(1., fluid1, force1, v1, v2, v3));
    cout << prox.get(v1) << " " << prox.get(v2) <<  " " << prox.get(v3) << endl;
    for (auto j: prox.map) {
        cout << j.first << " ";
        for (std::shared_ptr<particle> k : j.second) {
            cout << k->curr_pos.v[0] << " " << endl;
            for (auto i: k->forces)
                cout << i->apply(v3).v[2] << ' ';
        }
    }
    cout << endl;
    cout << sizeof(particle) << endl;
    return 0;
}