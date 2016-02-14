#include <kernel/KernelSpiky.hh>
#include "kernelTest.hh"

TEST_CASE( "Kernel return the correct maxDistance", "[kernel]") {
    SECTION( "Kernel Poly6") {
        KernelPoly6 k1(5.);
        REQUIRE(k1.maxDistance() == 5.);
    };
    SECTION( "Kernel Sine") {
        KernelSine k1(5.);
        REQUIRE(k1.maxDistance() == 5.);
    };
    SECTION( "Kernel Spiky") {
        KernelSpiky k1(5.);
        REQUIRE(k1.maxDistance() == 5.);
    };
    SECTION( "Kernel Viscosity") {
        KernelViscosity k1(5.);
        REQUIRE(k1.maxDistance() == 5.);
    };
};

TEST_CASE( "Kernel Value are null after maxRange", "[kernel]") {
    SECTION( "Kernel Poly6") {
        KernelPoly6 k1(5.);
        Vec3d v0 = Vec3d(1, 1, 1).normal() * k1.maxDistance() + Vec3d(0.1, 0.1, 0.1);
        Vec3d v1 = Vec3d(k1.gradW(v0));

        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);

        REQUIRE(v1.v[0] == 0);
        REQUIRE(v1.v[1] == 0);
        REQUIRE(v1.v[1] == 0);

        REQUIRE(k1.laplacianW(v0) == 0.);
    };
    SECTION( "Kernel Sine") {
        KernelSine k1(5.);
        Vec3d v0 = Vec3d(1, 1, 1).normal() * k1.maxDistance() + Vec3d(0.1, 0.1, 0.1);
        Vec3d v1 = Vec3d(k1.gradW(v0));

        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);

        REQUIRE(v1.v[0] == 0);
        REQUIRE(v1.v[1] == 0);
        REQUIRE(v1.v[1] == 0);
    };
    SECTION( "Kernel Spiky") {
        KernelSpiky k1(5.);
        Vec3d v0 = Vec3d(1, 1, 1).normal() * k1.maxDistance() + Vec3d(0.1, 0.1, 0.1);
        Vec3d v1 = Vec3d(k1.gradW(v0));

        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);

        REQUIRE(v1.v[0] == 0);
        REQUIRE(v1.v[1] == 0);
        REQUIRE(v1.v[1] == 0);

        REQUIRE(k1.laplacianW(v0) == 0.);
    };
    SECTION( "Kernel Viscosity") {
        KernelViscosity k1(5.);
        Vec3d v0 = Vec3d(1, 1, 1).normal() * k1.maxDistance() + Vec3d(0.1, 0.1, 0.1);
        Vec3d v1 = Vec3d(k1.gradW(v0));

        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);

        REQUIRE(v1.v[0] == 0);
        REQUIRE(v1.v[1] == 0);
        REQUIRE(v1.v[1] == 0);

        REQUIRE(k1.laplacianW(v0) == 0.);
    };
};

TEST_CASE( "Kernel Value are less than 1 at 0", "[kernel]") {
    SECTION( "Kernel Poly6") {
        KernelPoly6 k1(5.);
        REQUIRE(k1.W(0.) <= 1.);
    }
    SECTION( "Kernel Sine") {
        KernelSine k1(5.);
        REQUIRE(k1.W(0.) <= 1.);
    }
    SECTION( "Kernel Spiky") {
        KernelSpiky k1(5.);
        REQUIRE(k1.W(0.) <= 1.);
    }
    SECTION( "Kernel Viscosity") {
        KernelViscosity k1(5.);
        // REQUIRE(k1.W(0.) <= 1.);
    }
};