#define CATCH_CONFIG_RUNNER

#define CATCH_CONFIG_CPP11_NULLPTR              // nullptr is supported?
#define CATCH_CONFIG_CPP11_NOEXCEPT             // noexcept is supported?
#define CATCH_CONFIG_CPP11_GENERATED_METHODS    // delete and default keywords for methods
#define CATCH_CONFIG_CPP11_IS_ENUM              // std::is_enum is supported?
#define CATCH_CONFIG_CPP11_TUPLE                // std::tuple is supported
#define CATCH_CONFIG_VARIADIC_MACROS            // Usually pre-C++11 compiler extensions are sufficient
#define CATCH_CONFIG_CPP11_LONG_LONG            // generates overloads for the long long type
#define CATCH_CONFIG_CPP11_OVERRIDE             // CATCH_OVERRIDE expands to override (for virtual function implementations)
#define CATCH_CONFIG_CPP11_UNIQUE_PTR           // Use std::unique_ptr instead of std::auto_ptr

#include "catch.hpp"

#include "spdlog/spdlog.h"
namespace spd = spdlog;

int main( int argc, char* argv[] )
{
    auto console = spd::stdout_logger_mt("console");
    spd::set_level(spd::level::err);

    int result = Catch::Session().run( argc, argv );
    return result;
}
