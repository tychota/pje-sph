#include <kernel/KernelSpiky.hpp>
#include "kernelTest.hpp"

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
    vec3 v00 = {1, 1, 1};
    vec3 eps = {0.1, 0.1, 0.1};

    SECTION( "Kernel Poly6") {
        KernelPoly6 k1(5.);
        vec3 v0 = normalise(v00) * k1.maxDistance() + eps;
        vec3 v1 = vec3(k1.gradW(v0));

        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);

        REQUIRE(v1[0] == 0);
        REQUIRE(v1[1] == 0);
        REQUIRE(v1[2] == 0);

        REQUIRE(k1.laplacianW(v0) == 0.);
    };
    SECTION( "Kernel Sine") {
        KernelSine k1(5.);
        vec3 v0 = normalise(v00) * k1.maxDistance() + eps;
        vec3 v1 = vec3(k1.gradW(v0));

        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);

        REQUIRE(v1[0] == 0);
        REQUIRE(v1[1] == 0);
        REQUIRE(v1[2] == 0);
    };
    SECTION( "Kernel Spiky") {
        KernelSpiky k1(5.);
        vec3 v0 = normalise(v00) * k1.maxDistance() + eps;
        vec3 v1 = vec3(k1.gradW(v0));

        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);

        REQUIRE(v1[0] == 0);
        REQUIRE(v1[1] == 0);
        REQUIRE(v1[2] == 0);

        REQUIRE(k1.laplacianW(v0) == 0.);
    };
    SECTION( "Kernel Viscosity") {
        KernelViscosity k1(5.);
        vec3 v0 = normalise(v00) * k1.maxDistance() + eps;
        vec3 v1 = vec3(k1.gradW(v0));

        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);

        REQUIRE(v1[0] == 0);
        REQUIRE(v1[1] == 0);
        REQUIRE(v1[2] == 0);

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
