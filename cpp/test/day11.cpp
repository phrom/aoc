#include <catch2/catch.hpp>

#include "day11.hpp"

TEST_CASE("Day 11: Dumbo Octopus")
{
    const char* input = R"(5483143223
2745854711
5264556173
6141336146
6357385478
4167524645
2176841721
6882881134
4846848554
5283751526
)";

    SECTION("Parse")
    {
        const auto cavern = day11::parse(input);
        REQUIRE(
            cavern ==
            day11::cavern{ std::array{
                std::array<uint64_t, 10>{ 5, 4, 8, 3, 1, 4, 3, 2, 2, 3 },
                std::array<uint64_t, 10>{ 2, 7, 4, 5, 8, 5, 4, 7, 1, 1 },
                std::array<uint64_t, 10>{ 5, 2, 6, 4, 5, 5, 6, 1, 7, 3 },
                std::array<uint64_t, 10>{ 6, 1, 4, 1, 3, 3, 6, 1, 4, 6 },
                std::array<uint64_t, 10>{ 6, 3, 5, 7, 3, 8, 5, 4, 7, 8 },
                std::array<uint64_t, 10>{ 4, 1, 6, 7, 5, 2, 4, 6, 4, 5 },
                std::array<uint64_t, 10>{ 2, 1, 7, 6, 8, 4, 1, 7, 2, 1 },
                std::array<uint64_t, 10>{ 6, 8, 8, 2, 8, 8, 1, 1, 3, 4 },
                std::array<uint64_t, 10>{ 4, 8, 4, 6, 8, 4, 8, 5, 5, 4 },
                std::array<uint64_t, 10>{ 5, 2, 8, 3, 7, 5, 1, 5, 2, 6 } } });
    }

    SECTION("Part 1") { REQUIRE(day11::part1(input) == 1656); }

    SECTION("Part 2") { REQUIRE(day11::part2(input) == 0); }
}
