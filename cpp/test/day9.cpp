#include <catch2/catch.hpp>

#include "day9.hpp"
#include "read_file.hpp"

TEST_CASE("Day 9: Smoke Basin")
{
    const char* input =
        R"(2199943210
3987894921
9856789892
8767896789
9899965678
)";

    SECTION("Parse")
    {
        const auto heightmap = day9::parse(input);
        REQUIRE(
            heightmap ==
            day9::heightmap{ { { 2, 1, 9, 9, 9, 4, 3, 2, 1, 0 },
                               { 3, 9, 8, 7, 8, 9, 4, 9, 2, 1 },
                               { 9, 8, 5, 6, 7, 8, 9, 8, 9, 2 },
                               { 8, 7, 6, 7, 8, 9, 6, 7, 8, 9 },
                               { 9, 8, 9, 9, 9, 6, 5, 6, 7, 8 } } });
    }

    SECTION("Part 1") { REQUIRE(day9::part1(input) == 15); }

    SECTION("Part 2") { REQUIRE(day9::part2(input) == 1134); }

    SECTION("Full input")
    {
        const auto file = read_file("day9.txt");
        REQUIRE(day9::part1(file) == 550);
        REQUIRE(day9::part2(file) == 1100682);
    }
}
