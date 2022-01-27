#include <catch2/catch.hpp>

#include "day17.hpp"

TEST_CASE("Day 17: Trick Shot")
{
    const auto input = "target area: x=20..30, y=-10..-5";
    SECTION("Parse")
    {
        REQUIRE(
            day17::parse(input) == day17::probe_launcher{ day17::target_area{
                                       { 20, 30 }, { -10, -5 } } });
    }
    SECTION("Part 1") { REQUIRE(day17::part1(input) == 45); }
}
