#include "solidTest.hh"

TEST_CASE("Calcul of tangential reaction is working", "[solid]") {
    SECTION("Non already tangent vector return the right projection") {
        Vec3d normal = Vec3d(0, 0 , 1);
        Vec3d incomming = Vec3d(1, 0, -1);
        Vec3d tangent = tangentialIncoming(incomming, normal);

        REQUIRE(tangent[0] == 1.);
        REQUIRE(tangent[1] == 0.);
        REQUIRE(tangent[2] == 0.);
    };
    SECTION("Non already tangent vector return the right projection") {
        Vec3d normal = Vec3d(0, 1 , 0);
        Vec3d incomming = Vec3d(1, 0, 0);
        Vec3d tangent = tangentialIncoming(incomming, normal);

        REQUIRE(tangent[0] == 1.);
        REQUIRE(tangent[1] == 0.);
        REQUIRE(tangent[2] == 0.);
    };
};