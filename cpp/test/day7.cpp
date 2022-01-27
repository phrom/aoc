#include <catch2/catch.hpp>

#include "day7.hpp"
#include "read_file.hpp"

TEST_CASE("Day 7: The Treachery of Whales")
{
    const char* input = "16,1,2,0,4,2,7,1,2,14";

    SECTION("Input is parsed correctly")
    {
        auto crabs = day7::parse(input);
        REQUIRE(crabs == day7::crabs{ { 16, 1, 2, 0, 4, 2, 7, 1, 2, 14 } });
    }

    SECTION("Part 1") { REQUIRE(day7::part1(input) == 37); }

    SECTION("Part 2") { REQUIRE(day7::part2(input) == 168); }

    SECTION("Full input")
    {
        const auto file = read_file("day7.txt");
        REQUIRE(day7::part1(file) == 353800);
        REQUIRE(day7::part2(file) == 98119739);
    }
}
