#define CATCH_CONFIG_RUNNER
#include "catch.hh"

#include "spdlog/spdlog.h"
namespace spd = spdlog;

int main( int argc, char* argv[] )
{
    auto console = spd::stdout_logger_mt("console");
    spd::set_level(spd::level::err);

    int result = Catch::Session().run( argc, argv );
    return result;
}