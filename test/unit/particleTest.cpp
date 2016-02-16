#include "particleTest.hpp"

TEST_CASE( "It is possible to create and modify a particle", "[particle]" ) {
    Fluid fluid1(1000, 0.1, 0.001, 0.2, 2, 0.1, 0.7);
    vec3 g = {0, 0, -9.8};
    shared_ptr<Force> gravity = make_shared<Force>(g);
    listForces forces{gravity};
    KernelPoly6 kp6 = KernelPoly6(0.2);
    KernelSpiky ksp = KernelSpiky(0.2);
    KernelViscosity kv = KernelViscosity(0.2);
    Particle p1 = Particle(0.1, fluid1, forces, kp6, ksp, kv, kp6);
    Particle p2 = Particle(0.1, fluid1, forces, kp6, ksp, kv, kp6);
    SECTION( "Accessing fluid is possible" ) {
        REQUIRE(p1.flu.rho0 ==  1000);
    };
    SECTION( "Access forces" ) {
        for (auto f: p1.ext_forces) {
            REQUIRE(f->F()[2] == -9.8);
        }
    };
    SECTION( "Access kernels is possible" ) {
        REQUIRE(p1.fieldKernel.maxDistance() == 0.2);
    };
    SECTION( "Modifying State is possible" ) {
        vec3 vn = {1, 2, 3};
        p1.colour = 1.0;
        p1.colourLaplacian = 1.0;

        p1.colourDirection = vn;

        p1.curr_acc = vn;
        p1.curr_spe = vn;
        p1.curr_pos = vn;

        p1.next_acc = vn;
        p1.next_spe = vn;
        p1.next_pos = vn;

        p1.reac_pos = vn;
        p1.reac_spe = vn;

        REQUIRE(p1.colour == 1.0);
        REQUIRE(p1.colourLaplacian == 1.0);

        REQUIRE(p1.colourDirection[0] == 1.0);
        REQUIRE(p1.curr_acc[0] == 1.0);
        REQUIRE(p1.curr_spe[0] == 1.0);
        REQUIRE(p1.curr_pos[0] == 1.0);
        REQUIRE(p1.next_acc[0] == 1.0);
        REQUIRE(p1.next_spe[0] == 1.0);
        REQUIRE(p1.next_pos[0] == 1.0);
        REQUIRE(p1.reac_pos[0] == 1.0);
        REQUIRE(p1.reac_pos[0] == 1.0);
        REQUIRE(p1.reac_spe[0] == 1.0);
    };
    SECTION( "UpdateField does update the field" ) {
        Fluid fluid2(1000, 0.1, 0.001, 0.2, 2, 0.1, 0.7);
        vec3 g = {0, 0, -9.8};
        shared_ptr<Force> gravity = make_shared<Force>(g);
        listForces forces1{gravity};
        KernelPoly6 kp61 = KernelPoly6(0.2);
        KernelSpiky ksp1 = KernelSpiky(0.2);
        KernelViscosity kv1 = KernelViscosity(0.2);
        Particle p3 = Particle(0.1, fluid2, forces1, kp61, ksp1, kv1, kp61);
        p3.curr_pos = {1, 2, 3};
        shared_ptr<Particle> p3s = make_shared<Particle>(p3);
        Particle p4 = Particle(0.1, fluid2, forces1, kp61, ksp1, kv1, kp61);
        p4.curr_pos = {1, 2, 3.01};
        shared_ptr<Particle> p4s = make_shared<Particle>(p4);
        vector<shared_ptr<Particle>> vp1 = {p4s};
        p3.updateField(vp1);
        REQUIRE(p3.density - 814.1755245657 < 1e-5);
        REQUIRE(p3.colour - 0.8141755243 < 1e-5);
        REQUIRE(p3.colourDirection[1] == 0);
        REQUIRE(p3.colourDirection[2] - 1.2243240967 < 1e-5);
        REQUIRE(p3.colourDirection[3] == 0);
        REQUIRE(p3.colourLaplacian + 366.0698364258 < 1e-5);
    };
};
