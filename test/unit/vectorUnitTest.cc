#include "vectorUnitTest.hh"

TEST_CASE( "Vector related units tests", "[vector]" ) {
    Vec3d v1(0, 1, 2);
    Vec3d v1b(v1);
    SECTION ("created with Vec3d(x, y, z)") {
        REQUIRE(v1.v[0] == 0);
        REQUIRE(v1.v[1] == 1);
        REQUIRE(v1.v[2] == 2);
    }
    SECTION ("created with Vec3d(&Vec3d)") {
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