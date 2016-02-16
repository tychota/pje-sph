#include "solidTest.hpp"

TEST_CASE("Calcul of tangential reaction is working", "[solid]") {
    SECTION("Non already tangent vector return the right projection") {
        vec3 normal = {0, 0 , 1};
        vec3 incomming = {1, 0, -1};
        vec3 tangent = tangentialIncoming(incomming, normal);

        REQUIRE(tangent[0] == 1.);
        REQUIRE(tangent[1] == 0.);
        REQUIRE(tangent[2] == 0.);
    };
    SECTION("Non already tangent vector return the right projection") {
        vec3 normal = {0, 1 , 0};
        vec3 incomming = {1, 0, 0};
        vec3 tangent = tangentialIncoming(incomming, normal);

        REQUIRE(tangent[0] == 1.);
        REQUIRE(tangent[1] == 0.);
        REQUIRE(tangent[2] == 0.);
    };
};
