#include <catch2/catch.hpp>

#include "day1.hpp"

TEST_CASE("Day 1: Sonar Sweep")
{
    const char* input = R"(199
200
208
210
200
207
240
269
260
263)";

    SECTION("Part 1 - How many measurements are larger than the previous measurement?")
    {
        REQUIRE(day1::part1(input) == 7);
    }

    SECTION(
        "Part 2 - How many sums of 3 measurement sliding windows are larger than the previous sum?")
    {
        REQUIRE(day1::part2(input) == 5);
    }
}
