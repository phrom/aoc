#include <catch2/catch.hpp>

#include "day2.hpp"
#include "read_file.hpp"

TEST_CASE("Day 2: Dive!")
{
    const char* input = R"(forward 5
down 5
forward 8
up 3
down 8
forward 2)";

    SECTION("Part 1 - What do you get if you multiply your final horizontal "
            "position by your final "
            "depth?")
    {
        REQUIRE(day2::part1(input) == 150);
    }

    SECTION("Part 2 - What do you get if you multiply your final horizontal "
            "position by your final "
            "depth?")
    {
        REQUIRE(day2::part2(input) == 900);
    }

    SECTION("Full input")
    {
        const auto file = read_file("day2.txt");
        REQUIRE(day2::part1(file) == 1855814);
        REQUIRE(day2::part2(file) == 1845455714);
    }
}
