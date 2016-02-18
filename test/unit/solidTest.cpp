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
    SECTION("Rotate (1, 0, 0) around z axis by 90° gives (0, 1, 0)") {
        VEC rot = {0, 0 , PI/2};
        VEC v_old = {1, 0, 0};
        VEC v_new = rotateCoord(v_old, rot);

        REQUIRE(v_new[0] < 1e-5);
        REQUIRE(v_new[1] - 1 < 1e-5);
        REQUIRE(v_new[2] < 1e-5);
    };
    SECTION("Rotate (1, 0, 0) around y axis by 90° gives (0, 0, 1)") {
        VEC rot = {0, PI/2, 0};
        VEC v_old = {1, 0, 0};
        VEC v_new = rotateCoord(v_old, rot);

        REQUIRE(v_new[0] < 1e-5);
        REQUIRE(v_new[1] < 1e-5);
        REQUIRE(v_new[2] - 1 < 1e-5);
    };
    SECTION("Rotate (1, 0, 0) around z axis by 90° gives (1, 0, 0)") {
        VEC rot = {PI/2, 0, 0};
        VEC v_old = {1, 0, 0};
        VEC v_new = rotateCoord(v_old, rot);

        REQUIRE(v_new[0] - 1 < 1e-5);
        REQUIRE(v_new[1] < 1e-5);
        REQUIRE(v_new[2] < 1e-5);
    };
};

TEST_CASE( "Box collison is working" ) {
    SECTION("Unit cube, center in 0, in the same repere as the global one, particle located up ther cube") {
        VEC v0 = {0., 0., 0.};
        VEC v1 = {1., 1., 1.};
        Box b1(0.2, SolidType::Recipient, v0, v0, v1);

        Fluid fluid1(1000, 0.001, 0.2, 2, 0.1, 0.7);
        shared_ptr<Fluid> f1 = make_shared<Fluid>(fluid1);
        VEC g = {0, 0, -9.8};
        shared_ptr<Force> gravity = make_shared<Force>(g);
        listForces forces{gravity};
        shared_ptr<listForces> lf = make_shared<listForces>(forces);

        shared_ptr<KernelPoly6> kp6 = make_shared<KernelPoly6>(0.2);
        shared_ptr<KernelSpiky> ksp = make_shared<KernelSpiky>(0.2);
        shared_ptr<KernelViscosity> kv = make_shared<KernelViscosity>(0.2);

        Particle p1 = Particle(0.1, f1, lf, kp6, ksp, kv, kp6, 1);

        p1.next_pos = {0.5, 0.5, 1.1};
        p1.next_spe = {1, 1, 1};

        REQUIRE(b1.detect(v1));

        b1.react(p1, 0.1);

        REQUIRE(abs(p1.next_pos[0] - 0.5) < 1e-5);
        REQUIRE(abs(p1.next_pos[1] - 0.5) < 1e-5);
        REQUIRE(abs(p1.next_pos[2] - 1) < 1e-5);

        REQUIRE(abs(p1.next_spe[0] - 0.8) < 1e-5);
        REQUIRE(abs(p1.next_spe[1] - 0.8) < 1e-5);
        REQUIRE(abs(p1.next_spe[2] + 0.7) < 1e-5);
    };
    SECTION("Unit cube, center in 0, in the same repere as the global one, particle located down ther cube") {
        VEC v0 = {0., 0., 0.};
        VEC v1 = {1., 1., 1.};
        Box b1(0.2, SolidType::Recipient, v0, v0, v1);

        Fluid fluid1(1000, 0.001, 0.2, 2, 0.1, 0.7);
        shared_ptr<Fluid> f1 = make_shared<Fluid>(fluid1);
        VEC g = {0, 0, -9.8};
        shared_ptr<Force> gravity = make_shared<Force>(g);
        listForces forces{gravity};
        shared_ptr<listForces> lf = make_shared<listForces>(forces);

        shared_ptr<KernelPoly6> kp6 = make_shared<KernelPoly6>(0.2);
        shared_ptr<KernelSpiky> ksp = make_shared<KernelSpiky>(0.2);
        shared_ptr<KernelViscosity> kv = make_shared<KernelViscosity>(0.2);

        Particle p1 = Particle(0.1, f1, lf, kp6, ksp, kv, kp6, 1);

        p1.next_pos = {0.5, 0.5, -1.1};
        p1.next_spe = {-1, -1, -1};

        REQUIRE(b1.detect(v1));

        b1.react(p1, 0.1);

        REQUIRE(abs(p1.next_pos[0] - 0.5) < 1e-5);
        REQUIRE(abs(p1.next_pos[1] - 0.5) < 1e-5);
        REQUIRE(abs(p1.next_pos[2] + 1) < 1e-5);

        REQUIRE(abs(p1.next_spe[0] + 0.8) < 1e-5);
        REQUIRE(abs(p1.next_spe[1] + 0.8) < 1e-5);
        REQUIRE(abs(p1.next_spe[2] - 0.7) < 1e-5);
    };
    SECTION("Non unit cube, center in 0, in the same repere as the global one, particle located down ther cube") {
        VEC v0 = {0., 0., 0.};
        VEC v1 = {2., 2., 2.};
        Box b1(0.2, SolidType::Recipient, v0, v0, v1);

        Fluid fluid1(1000, 0.001, 0.2, 2, 0.1, 0.7);
        shared_ptr<Fluid> f1 = make_shared<Fluid>(fluid1);
        VEC g = {0, 0, -9.8};
        shared_ptr<Force> gravity = make_shared<Force>(g);
        listForces forces{gravity};
        shared_ptr<listForces> lf = make_shared<listForces>(forces);

        shared_ptr<KernelPoly6> kp6 = make_shared<KernelPoly6>(0.2);
        shared_ptr<KernelSpiky> ksp = make_shared<KernelSpiky>(0.2);
        shared_ptr<KernelViscosity> kv = make_shared<KernelViscosity>(0.2);

        Particle p1 =Particle(0.1, f1, lf, kp6, ksp, kv, kp6, 1);

        p1.next_pos = {0.5, 0.5, -2.1};
        p1.next_spe = {-1, -1, -1};

        REQUIRE(b1.detect(v1));

        b1.react(p1, 0.1);

        REQUIRE(abs(p1.next_pos[0] - 0.5) < 1e-5);
        REQUIRE(abs(p1.next_pos[1] - 0.5) < 1e-5);
        REQUIRE(abs(p1.next_pos[2] + 2) < 1e-5);
    };
    SECTION("Non unit cube, not center in 0, in the same repere as the global one, particle located down ther cube") {
        VEC v0 = {0., 1., 0.};
        VEC vr = {0., 0., 0.};
        VEC v1 = {2., 2., 2.};
        Box b1(0.2, SolidType::Recipient, v0, vr, v1);

        Fluid fluid1(1000, 0.001, 0.2, 2, 0.1, 0.7);
        shared_ptr<Fluid> f1 = make_shared<Fluid>(fluid1);
        VEC g = {0, 0, -9.8};
        shared_ptr<Force> gravity = make_shared<Force>(g);
        listForces forces{gravity};
        shared_ptr<listForces> lf = make_shared<listForces>(forces);

        shared_ptr<KernelPoly6> kp6 = make_shared<KernelPoly6>(0.2);
        shared_ptr<KernelSpiky> ksp = make_shared<KernelSpiky>(0.2);
        shared_ptr<KernelViscosity> kv = make_shared<KernelViscosity>(0.2);

        Particle p1 = Particle(0.1, f1, lf, kp6, ksp, kv, kp6, 1);

        p1.next_pos = {0.5, 1.5, -2.1};
        p1.next_spe = {-1, -1, -1};

        REQUIRE(b1.detect(v1));

        b1.react(p1, 0.1);

        REQUIRE(abs(p1.next_pos[0] - 0.5) < 1e-5);
        REQUIRE(abs(p1.next_pos[1] - 1.5) < 1e-5);
        REQUIRE(abs(p1.next_pos[2] + 2) < 1e-5);
    };
}
