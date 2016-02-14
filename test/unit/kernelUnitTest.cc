#include "kernelUnitTest.hh"

TEST_CASE( "Kernel return the correct maxDistance", "[kernel]") {
    SECTION( "Kernel Box") {
        KernelBox k1(5.);
        REQUIRE(k1.maxDistance() == 5.);
    }
    SECTION( "Kernel Cusp") {
        KernelCusp k1(5.);
        REQUIRE(k1.maxDistance() == 5.);
    }
    SECTION( "Kernel Gaussian") {
        KernelGaussian k1(5.);
        REQUIRE(k1.maxDistance() == 25.);
    }
    SECTION( "Kernel Quadratic") {
        KernelQuadratic k1(5.);
        REQUIRE(k1.maxDistance() == 10.);
    }
    SECTION( "Kernel Spline 3rd Order") {
        KernelSpline3rdO k1(5.);
        REQUIRE(k1.maxDistance() == 10.);
    }
    SECTION( "Kernel Spline 5rd Order") {
        KernelSpline5rdO k1(5.);
        REQUIRE(k1.maxDistance() == 15.);
    }
    SECTION( "Kernel Spline Beta Order") {
        KernelSplineBeta k1(5.);
        REQUIRE(k1.maxDistance() == 5.);
    }
};

TEST_CASE( "Kernel Value are null after maxRange", "[kernel]") {
    SECTION( "Kernel Box") {
        KernelBox k1(5.);
        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);
    }
    SECTION( "Kernel Cusp") {
        KernelCusp k1(5.);
        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);
    }
    SECTION( "Kernel Gaussian") {
        KernelGaussian k1(5.);
        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);
    }
    SECTION( "Kernel Quadratic") {
        KernelQuadratic k1(5.);
        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);
    }
    SECTION( "Kernel Spline 3rd Order") {
        KernelSpline3rdO k1(5.);
        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);
    }
    SECTION( "Kernel Spline 5rd Order") {
        KernelSpline5rdO k1(5.);
        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);
    }
    SECTION( "Kernel Spline Beta Order") {
        KernelSplineBeta k1(5.);
        REQUIRE(k1.W(k1.maxDistance() + 0.1) == 0.);
    }
};

TEST_CASE( "Kernel Value are less than 1 at 0", "[kernel]") {
    SECTION( "Kernel Box") {
        KernelBox k1(5.);
        REQUIRE(k1.W(0.) <= 1.);
    }
    SECTION( "Kernel Cusp") {
        KernelCusp k1(5.);
        REQUIRE(k1.W(0.) <= 1.);
    }
    SECTION( "Kernel Gaussian") {
        KernelGaussian k1(5.);
        REQUIRE(k1.W(0.) <= 1.);
    }
    SECTION( "Kernel Quadratic") {
        KernelQuadratic k1(5.);
        REQUIRE(k1.W(0.) <= 1.);
    }
    SECTION( "Kernel Spline 3rd Order") {
        KernelSpline3rdO k1(5.);
        REQUIRE(k1.W(0.) <= 1.);
    }
    SECTION( "Kernel Spline 5rd Order") {
        KernelSpline5rdO k1(5.);
        REQUIRE(k1.W(0.) <= 1.);
    }
    SECTION( "Kernel Spline Beta Order") {
        KernelSplineBeta k1(5.);
        REQUIRE(k1.W(0.) <= 1.);
    }
};