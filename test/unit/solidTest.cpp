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

TEST_CASE("Calcul of vectorial rotation is working", "[solid]") {
    double pi = 3.141592653589793238462643383;
    SECTION("Rotate (1, 0, 0) around z axis by 90° gives (0, 1, 0)") {
        vec3 rot = {0, 0 , pi/2};
        vec3 v_old = {1, 0, 0};
        vec3 v_new = rotateCoord(v_old, rot);

        REQUIRE(v_new[0] < 1e-5);
        REQUIRE(v_new[1] - 1 < 1e-5);
        REQUIRE(v_new[2] < 1e-5);
    };
    SECTION("Rotate (1, 0, 0) around y axis by 90° gives (0, 0, 1)") {
        vec3 rot = {0, pi/2, 0};
        vec3 v_old = {1, 0, 0};
        vec3 v_new = rotateCoord(v_old, rot);

        REQUIRE(v_new[0] < 1e-5);
        REQUIRE(v_new[1] < 1e-5);
        REQUIRE(v_new[2] - 1 < 1e-5);
    };
    SECTION("Rotate (1, 0, 0) around z axis by 90° gives (1, 0, 0)") {
        vec3 rot = {pi/2, 0, 0};
        vec3 v_old = {1, 0, 0};
        vec3 v_new = rotateCoord(v_old, rot);

        REQUIRE(v_new[0] - 1 < 1e-5);
        REQUIRE(v_new[1] < 1e-5);
        REQUIRE(v_new[2] < 1e-5);
    };
};
