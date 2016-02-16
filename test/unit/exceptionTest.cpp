#include "exceptionTest.hpp"

TEST_CASE( "Exception", "[Exception]") {
    REQUIRE_THROWS(throw NotImplementedException(););
}
