#include <catch2/catch.hpp>

#include "day3.hpp"

TEST_CASE("Day 3: Binary Diagnostic")
{
    const char* input = R"(00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010)";

    SECTION("Part 1 - What is the power consumption of the submarine?")
    {
        REQUIRE(day3::part1(input) == 198);
    }

    SECTION("Part 2 - What is the life support rating of the submarine?")
    {
        REQUIRE(day3::part2(input) == 230);
    }
}
