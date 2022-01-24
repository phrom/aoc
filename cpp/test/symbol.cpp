#include <catch2/catch.hpp>

#include "symbol.hpp"

#include <set>

TEST_CASE("Symbol")
{
    const auto s1 = symbol{ "s1" };
    const auto s2 = symbol{ "s2" };
    const auto s3 = symbol{ "s1" };
    REQUIRE(s1 != s2);
    REQUIRE(s1 == s3);
    REQUIRE(s1.to_str() == "s1");
    REQUIRE(s2.to_str() == "s2");
    REQUIRE(s3.to_str() == "s1");
    std::set<symbol> s = { s1, s2, s3 };
    REQUIRE(s.contains(s1));
    REQUIRE(s.contains(symbol{ "s2" }));
    REQUIRE(!s.contains(symbol{ "s3" }));
}
