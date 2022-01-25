#include <catch2/catch.hpp>

#include "day15.hpp"

TEST_CASE("Day 15: Chiton")
{
    const char* input = R"(1163751742
1381373672
2136511328
3694931569
7463417111
1319128137
1359912421
3125421639
1293138521
2311944581
)";

    SECTION("Part 1") { REQUIRE(day15::part1(input) == 40); }
    SECTION("Part 2") { REQUIRE(day15::part2(input) == 0); }
}
