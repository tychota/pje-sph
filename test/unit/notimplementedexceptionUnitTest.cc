#include "notimplementedexceptionUnitTest.hh"

TEST_CASE( "Exception", "[Exception]") {
    REQUIRE_THROWS(throw NotImplementedException(););
}