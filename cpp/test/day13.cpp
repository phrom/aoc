#include <catch2/catch.hpp>

#include "day13.hpp"

TEST_CASE("Day 13: Transparent Origami")
{
    const char* input = R"(6,10
0,14
9,10
0,3
10,4
4,11
6,0
6,12
4,1
0,13
10,12
3,4
3,0
8,4
1,10
2,14
8,10
9,0

fold along y=7
fold along x=5
)";

    SECTION("Part 1") { REQUIRE(day13::part1(input) == 17); }
}
