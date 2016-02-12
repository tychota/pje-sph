#define CATCH_CONFIG_MAIN
#include "catch.hh"

#include "common/fluid.hh"
#include "common/particle.hh"
#include "structure/proximityHash.hh"
#include "utils/vec3.hh"

TEST_CASE( "Vector related units tests", "[vector]" ) {
    vec3d v1(0, 1, 2);
    vec3d v1b(v1);
    SECTION ("created with vec3d(x, y, z)") {
        REQUIRE(v1.v[0] == 0);
        REQUIRE(v1.v[1] == 1);
        REQUIRE(v1.v[2] == 2);
    }
    SECTION ("created with vec3d(&vec3d)") {
        REQUIRE(v1b.v[0] == 0);
        REQUIRE(v1b.v[1] == 1);
        REQUIRE(v1b.v[2] == 2);
    }
    v1b.v[0] = 1;
    SECTION ("vopied and not linked") {
        REQUIRE(v1.v[0] == 0);
        REQUIRE(v1b.v[0] == 1);
    }
}

TEST_CASE( "Fluid related units tests", "[fluid]") {
    fluid fluid1(1000, 0.1, 0.001, 0.2, 2, 0.1, 0.7);
}

TEST_CASE( "Proximity Hash related units tests", "[hash]") {
    proximityHash hash1(1, 100);
    SECTION( "Hash of null vector is 0" ) {
        REQUIRE(hash1.get(vec3d(0, 0, 0)) == 0);
    }
    SECTION( "Neighbour particules have the same hash" ) {
        REQUIRE(hash1.get(vec3d(0, 0, 0)) == hash1.get(vec3d(0.9, 0.9, 0.9)));
        REQUIRE(hash1.get(vec3d(-0.9, -0.9, -0.9)) == hash1.get(vec3d(-0.1, -0.1, -0.1)));
    }
    SECTION( "Particles can be added" ) {
        fluid fluid1(1000, 0.1, 0.001, 0.2, 2, 0.1, 0.7);
        shared_ptr<force> gravity = make_shared<force>(uniform(vec3d(0, 0, -9.8)));
        listForces forces {gravity};
        shared_ptr<particle> p1 = make_shared<particle>(0.1, fluid1, forces);
        shared_ptr<particle> p2 = make_shared<particle>(0.1, fluid1, forces);
        p1->curr_pos = vec3d(0, 0, 0);
        p2->curr_pos = vec3d(0.1, 0, 0);
        hash1.add(p1);
        hash1.add(p2);
        // Check if map got the 0 key
        unordered_map<int64_t, set<shared_ptr<particle>>>::iterator it1 = hash1.map.find(0);
        REQUIRE(it1 != hash1.map.end());
        // Check if the vector in map 0 contains p1 and p2
        set<shared_ptr<particle>>* s = &it1->second;
        REQUIRE(s->find(p1) != s->end());
        REQUIRE(s->find(p2) != s->end());
    }
}