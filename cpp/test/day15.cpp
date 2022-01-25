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
    SECTION("repeated_matrix")
    {
        matrix<uint64_t> m;
        m.set(0, 0, 1);
        day15::repeated_matrix rm{ std::move(m), 5 };
        REQUIRE(rm.rows() == 5);
        REQUIRE(rm.columns(0) == 5);
        REQUIRE(rm.get(0, 0) == 1);
        REQUIRE(rm.get(0, 1) == 2);
        REQUIRE(rm.get(1, 0) == 2);
        REQUIRE(rm.get(0, 2) == 3);
        REQUIRE(rm.get(1, 1) == 3);
        REQUIRE(rm.get(2, 0) == 3);
        REQUIRE(rm.get(0, 3) == 4);
        REQUIRE(rm.get(1, 2) == 4);
        REQUIRE(rm.get(2, 1) == 4);
        REQUIRE(rm.get(3, 0) == 4);
        REQUIRE(rm.get(0, 4) == 5);
        REQUIRE(rm.get(1, 3) == 5);
        REQUIRE(rm.get(2, 2) == 5);
        REQUIRE(rm.get(3, 1) == 5);
        REQUIRE(rm.get(4, 0) == 5);
        REQUIRE(rm.get(1, 4) == 6);
        REQUIRE(rm.get(2, 3) == 6);
        REQUIRE(rm.get(3, 2) == 6);
        REQUIRE(rm.get(4, 1) == 6);
        REQUIRE(rm.get(2, 4) == 7);
        REQUIRE(rm.get(3, 3) == 7);
        REQUIRE(rm.get(4, 2) == 7);
        REQUIRE(rm.get(3, 4) == 8);
        REQUIRE(rm.get(4, 3) == 8);
        REQUIRE(rm.get(4, 4) == 9);
    }
    //    SECTION("Part 2") { REQUIRE(day15::part2(input) == 315); }
}
