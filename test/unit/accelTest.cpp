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
        VEC g = {0, 0, -9.8};
        shared_ptr<Force> gravity = make_shared<Force>(g);
        listForces forces{gravity};
        KernelPoly6 kp6 = KernelPoly6(3);
        KernelSpiky ksp = KernelSpiky(3);
        KernelViscosity kv = KernelViscosity(3);
        shared_ptr<Particle> p1 = make_shared<Particle>(0.1, fluid1, forces, kp6, ksp, kv, kp6);
        shared_ptr<Particle> p2 = make_shared<Particle>(0.1, fluid1, forces, kp6, ksp, kv, kp6);
        p1->curr_pos = {0, 0, 0};
        p2->curr_pos = {0.1, 0, 0};
        hash1.add(p1);
        hash1.add(p2);
        // Check if map got the 0 key
        unordered_map<int64_t, set<shared_ptr<Particle>>>::iterator it1 = hash1.map.find(0);
        REQUIRE(it1 != hash1.map.end());
        // Check if the vector in map 0 contains p1 and p2
        set<shared_ptr<Particle>> *s = &it1->second;
        REQUIRE(s->find(p1) != s->end());
        REQUIRE(s->find(p2) != s->end());
    }
}
