#include "particleTest.hpp"

TEST_CASE( "It is possible to create and modify a particle", "[particle]" ) {
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
    Particle p2 = Particle(0.1, f1, lf, kp6, ksp, kv, kp6, 2);

    SECTION( "Accessing fluid is possible" ) {
        REQUIRE(p1.flu->rho0 ==  1000);
    };
    SECTION( "Access forces" ) {
        for (auto f: *p1.ext_forces) {
            REQUIRE(f->F()[2] == -9.8);
        }
    };
    SECTION( "Access kernels is possible" ) {
        REQUIRE(p1.fieldKernel->maxDistance() == 0.2);
    };
    SECTION( "Modifying State is possible" ) {
        VEC vn = {1, 2, 3};
        p1.colour = 1.0;
        p1.colourLaplacian = 1.0;

        p1.colourDirection = vn;

        p1.curr_acc = vn;
        p1.curr_spe = vn;
        p1.curr_pos = vn;

        p1.next_acc = vn;
        p1.next_spe = vn;
        p1.next_pos = vn;

        REQUIRE(p1.colour == 1.0);
        REQUIRE(p1.colourLaplacian == 1.0);

        REQUIRE(p1.colourDirection[0] == 1.0);
        REQUIRE(p1.curr_acc[0] == 1.0);
        REQUIRE(p1.curr_spe[0] == 1.0);
        REQUIRE(p1.curr_pos[0] == 1.0);
        REQUIRE(p1.next_acc[0] == 1.0);
        REQUIRE(p1.next_spe[0] == 1.0);
        REQUIRE(p1.next_pos[0] == 1.0);
    };
    SECTION( "UpdateField does update the field" ) {
        Fluid fluid2(1000, 0.001, 0.2, 2, 0.1, 0.7);
        VEC g = {0, 0, -9.8};
        shared_ptr<Fluid> f2 = make_shared<Fluid>(fluid2);
        listForces forces1{gravity};
        shared_ptr<KernelPoly6> kp61 = make_shared<KernelPoly6>(0.2);
        shared_ptr<KernelSpiky> ksp1 = make_shared<KernelSpiky>(0.2);
        shared_ptr<KernelViscosity> kv1 = make_shared<KernelViscosity>(0.2);
        Particle p3 = Particle(0.1, f2, lf, kp61, ksp1, kv1, kp61, 3);
        p3.curr_pos = {1, 2, 3};
        shared_ptr<Particle> p3s = make_shared<Particle>(p3);
        Particle p4 = Particle(0.1, f2, lf, kp61, ksp1, kv1, kp61, 4);
        p4.curr_pos = {1, 2, 3.01};
        shared_ptr<Particle> p4s = make_shared<Particle>(p4);
        vector<shared_ptr<Particle>> vp1 = {p4s};
        p3.updateField(vp1);
        REQUIRE(abs(p3.density - 814.1755245657) < 1e-5);
        REQUIRE(abs(p3.colour - 0.8141755243) < 1e-5);
        REQUIRE(abs(p3.colourDirection[1]) < 1e-5);
        REQUIRE(abs(p3.colourDirection[2] - 1.2243240967 )< 1e-5);
        REQUIRE(abs(p3.colourDirection[3]) < 1e-5);
        REQUIRE(abs(p3.colourLaplacian + 366.0698364258) < 1e-5);
    };
};
