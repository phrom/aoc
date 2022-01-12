#include <catch2/catch.hpp>

#include "day6.hpp"

TEST_CASE("Day 6: Lanternfish")
{
    const char* input = "3,4,3,1,2";

    SECTION("Input is parsed correctly")
    {
        auto school = day6::parse(input);
        REQUIRE(school == day6::school{ { 3, 4, 3, 1, 2 } });
    }

    SECTION("Part 1") { REQUIRE(day6::part1(input) == 5934); }
    SECTION("Part 2") { REQUIRE(day6::part2(input) == 26984457539); }
}
