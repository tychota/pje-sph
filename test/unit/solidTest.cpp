#include "solidTest.hpp"

TEST_CASE("Calcul of tangential reaction is working", "[solid]") {
    SECTION("Non already tangent vector return the right projection") {
        VEC normal = {0, 0 , 1};
        VEC incomming = {1, 0, -1};
        VEC tangent = tangentialIncoming(incomming, normal);

        REQUIRE(abs(tangent[0] -1) < 1e-5);
        REQUIRE(tangent[1] == 0.);
        REQUIRE(tangent[2] == 0.);
    };
    SECTION("Non already tangent vector return the right projection") {
        VEC normal = {0, 1 , 0};
        VEC incomming = {1, 0, 0};
        VEC tangent = tangentialIncoming(incomming, normal);

        REQUIRE(tangent[0] == 1.);
        REQUIRE(tangent[1] == 0.);
        REQUIRE(tangent[2] == 0.);
    };
};

TEST_CASE("Calcul of vectorial rotation is working", "[solid]") {
    double pi = 3.141592653589793238462643383;
    SECTION("Rotate (1, 0, 0) around z axis by 90° gives (0, 1, 0)") {
        VEC rot = {0, 0 , pi/2};
        VEC v_old = {1, 0, 0};
        VEC v_new = rotateCoord(v_old, rot);

        REQUIRE(v_new[0] < 1e-5);
        REQUIRE(v_new[1] - 1 < 1e-5);
        REQUIRE(v_new[2] < 1e-5);
    };
    SECTION("Rotate (1, 0, 0) around y axis by 90° gives (0, 0, 1)") {
        VEC rot = {0, pi/2, 0};
        VEC v_old = {1, 0, 0};
        VEC v_new = rotateCoord(v_old, rot);

        REQUIRE(v_new[0] < 1e-5);
        REQUIRE(v_new[1] < 1e-5);
        REQUIRE(v_new[2] - 1 < 1e-5);
    };
    SECTION("Rotate (1, 0, 0) around z axis by 90° gives (1, 0, 0)") {
        VEC rot = {pi/2, 0, 0};
        VEC v_old = {1, 0, 0};
        VEC v_new = rotateCoord(v_old, rot);

        REQUIRE(v_new[0] - 1 < 1e-5);
        REQUIRE(v_new[1] < 1e-5);
        REQUIRE(v_new[2] < 1e-5);
    };
};

TEST_CASE( "Box collison is working" ) {
    SECTION("Unit cube, center in 0, in the same repere as the global one") {
        VEC v0 = {0., 0., 0.};
        VEC v1 = {1., 1., 1.};
        Box b1(1, SolidType::Recipient, v0, v0, v1);

        Fluid fluid1(1000, 0.1, 0.001, 0.2, 2, 0.1, 0.7);
        VEC g = {0, 0, -9.8};
        shared_ptr<Force> gravity = make_shared<Force>(g);
        listForces forces{gravity};
        KernelPoly6 kp6 = KernelPoly6(0.2);
        KernelSpiky ksp = KernelSpiky(0.2);
        KernelViscosity kv = KernelViscosity(0.2);
        shared_ptr<Particle> p1 = make_shared<Particle>(0.1, fluid1, forces, kp6, ksp, kv, kp6);

        p1->next_pos = {0.5, 0.5, 1.1};
        p1->next_spe = {1, 1, 1.1};

        REQUIRE(b1.detect(v1));

        b1.react(p1, 0.1);

        REQUIRE(abs(p1->next_pos[0] - 0.5) < 1e-5);
        REQUIRE(abs(p1->next_pos[0] - 0.5) < 1e-5);
        REQUIRE(p1->next_pos[2] - 1 < 1e-5);
        REQUIRE(p1->next_pos[2] - 1> -1e-5);
    };
}
