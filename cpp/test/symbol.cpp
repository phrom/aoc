#include <catch2/catch.hpp>

#include "symbol.hpp"

TEST_CASE("Symbol")
{
    const auto s1 = symbol{ "s1" };
    const auto s2 = symbol{ "s2" };
    const auto s3 = symbol{ "s1" };
    REQUIRE(s1 != s2);
    REQUIRE(s1 == s3);
}
