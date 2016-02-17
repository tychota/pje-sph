#include "accelTest.hpp"

TEST_CASE("Proximity Hash related units tests", "[hash]") {
    AccelerationMap hash1(1, 100);
    SECTION("Hash of null vector is 0") {
        VEC v0 = {0, 0, 0};
        REQUIRE(hash1.get(v0) == 0);
    }
    SECTION("Neighbour particules have the same hash") {
        VEC v0 = {0, 0, 0};
        VEC v1 = {0.9, 0.9, 0.9};
        VEC v2 = {-0.9, -0.9, -0.9};
        VEC v3 = {-0.1, -0.1, -0.1};
        REQUIRE(hash1.get(v0) == hash1.get(v1));
        REQUIRE(hash1.get(v2) == hash1.get(v3));
    }
    SECTION("Particles can be added") {
        Fluid fluid1(1000, 0.1, 0.001, 0.2, 2, 0.1, 0.7);
        shared_ptr<Fluid> f1 = make_shared<Fluid>(fluid1);
        VEC g = {0, 0, -9.8};
        shared_ptr<Force> gravity = make_shared<Force>(g);
        listForces forces{gravity};
        shared_ptr<listForces> lf = make_shared<listForces>(forces);

        shared_ptr<KernelPoly6> kp6 = make_shared<KernelPoly6>(0.2);
        shared_ptr<KernelSpiky> ksp = make_shared<KernelSpiky>(0.2);
        shared_ptr<KernelViscosity> kv = make_shared<KernelViscosity>(0.2);

        Particle p1(0.1, f1, lf, kp6, ksp, kv, kp6);
        Particle p2(0.1, f1, lf, kp6, ksp, kv, kp6);

        p1.curr_pos = {0, 0, 0};
        p2.curr_pos = {0.1, 0, 0};

        hash1.add(p1);
        hash1.add(p2);
        // Check if map got the 0 key
        ListParticleMap::iterator it1 = hash1._map.find(0);
        REQUIRE(it1 != hash1._map.end());
        // Check if the vector in map 0 contains p1 and p2
        ListParticle *s = &it1->second;
        REQUIRE(s->find(p1) != s->end());
        REQUIRE(s->find(p2) != s->end());
    }
}
