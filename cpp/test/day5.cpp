#include <catch2/catch.hpp>

#include "day5.hpp"
#include "read_file.hpp"

TEST_CASE("Day 5: Hydrothermal Venture")
{
    const char* input =
        R"(0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2
)";

    SECTION("Input is parsed correctly")
    {
        auto floor = day5::parse(input);
        REQUIRE(
            floor ==
            day5::floor{ std::vector<day5::line>{ { { 0, 9 }, { 5, 9 } },
                                                  { { 8, 0 }, { 0, 8 } },
                                                  { { 9, 4 }, { 3, 4 } },
                                                  { { 2, 2 }, { 2, 1 } },
                                                  { { 7, 0 }, { 7, 4 } },
                                                  { { 6, 4 }, { 2, 0 } },
                                                  { { 0, 9 }, { 2, 9 } },
                                                  { { 3, 4 }, { 1, 4 } },
                                                  { { 0, 0 }, { 8, 8 } },
                                                  { { 5, 5 }, { 8, 2 } } } });
    }

    SECTION("Part 1") { REQUIRE(day5::part1(input) == 5); }

    SECTION("Part 2") { REQUIRE(day5::part2(input) == 12); }

    SECTION("Full input")
    {
        const auto file = read_file("day5.txt");
        REQUIRE(day5::part1(file) == 5632);
        REQUIRE(day5::part2(file) == 22213);
    }
}
