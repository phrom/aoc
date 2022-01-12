#include <catch2/catch.hpp>

#include "day4.hpp"

TEST_CASE("Day 4: Giant Squid")
{
    const char* input =
        R"(7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
2  0 12  3  7
)";

    SECTION("Input is parsed correctly")
    {
        auto game = day4::parse(input);
        REQUIRE(game.numbers == std::vector<int>{ 7,  4, 9,  5,  11, 17, 23,
                                                  2,  0, 14, 21, 24, 10, 16,
                                                  13, 6, 15, 25, 12, 22, 18,
                                                  20, 8, 19, 3,  26, 1 });
        REQUIRE(game.boards.size() == 3);
        REQUIRE(game.boards[0] == day4::board{ 22, 13, 17, 11, 0,  8,  2, 23, 4,
                                               24, 21, 9,  14, 16, 7,  6, 10, 3,
                                               18, 5,  1,  12, 20, 15, 19 });
        REQUIRE(game.boards[1] == day4::board{ 3,  15, 0,  2,  22, 9, 18,
                                               13, 17, 5,  19, 8,  7, 25,
                                               23, 20, 11, 10, 24, 4, 14,
                                               21, 16, 12, 6 });
        REQUIRE(game.boards[2] == day4::board{ 14, 21, 17, 24, 4, 10, 16,
                                               15, 9,  19, 18, 8, 23, 26,
                                               20, 22, 11, 13, 6, 5,  2,
                                               0,  12, 3,  7 });
    }

    SECTION("Part 1 - What will your final score be if you choose that board?")
    {
        REQUIRE(day4::part1(input) == 4512);
    }

    SECTION("Part 2 - What will be the final score of the last board to win?")
    {
        REQUIRE(day4::part2(input) == 1924);
    }
}
