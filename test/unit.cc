#define CATCH_CONFIG_MAIN
#include "utils/catch.hh"

#include "utils/vec3.hh"

TEST_CASE( "Vector are created", "[vector]" ) {
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