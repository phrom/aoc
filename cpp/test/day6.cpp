#include <catch2/catch.hpp>

#include "day6.hpp"
#include "read_file.hpp"

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

    SECTION("Full input")
    {
        const auto file = read_file("day6.txt");
        REQUIRE(day6::part1(file) == 360761);
        REQUIRE(day6::part2(file) == 1632779838045);
    }
}
