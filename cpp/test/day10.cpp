#include <catch2/catch.hpp>

#include "day10.hpp"

TEST_CASE("Day 10: Syntax Scoring")
{
    const char* input = R"([({(<(())[]>[[{[]{<()<>>
[(()[<>])]({[<{<<[]>>(
{([(<{}[<>[]}>{[]{[(<()>
(((({<>}<{<{<>}{[]{[]{}
[[<[([]))<([[{}[[()]]]
[{[{({}]{}}([{[{{{}}([]
{<[[]]>}<{[{[{[]{()[[[]
[<(<(<(<{}))><([]([]()
<{([([[(<>()){}]>(<<{{
<{([{{}}[<[[[<>{}]]]>[]]
)";

    SECTION("Parse")
    {
        const auto chunks = day10::parse(input);
        REQUIRE(
            chunks == std::vector<day10::chunk>{
                          day10::chunk{ "[({(<(())[]>[[{[]{<()<>>" },
                          day10::chunk{ "[(()[<>])]({[<{<<[]>>(" },
                          day10::chunk{ "{([(<{}[<>[]}>{[]{[(<()>" },
                          day10::chunk{ "(((({<>}<{<{<>}{[]{[]{}" },
                          day10::chunk{ "[[<[([]))<([[{}[[()]]]" },
                          day10::chunk{ "[{[{({}]{}}([{[{{{}}([]" },
                          day10::chunk{ "{<[[]]>}<{[{[{[]{()[[[]" },
                          day10::chunk{ "[<(<(<(<{}))><([]([]()" },
                          day10::chunk{ "<{([([[(<>()){}]>(<<{{" },
                          day10::chunk{ "<{([{{}}[<[[[<>{}]]]>[]]" } });
    }

    SECTION("is_corrupted")
    {
        REQUIRE(day10::chunk{ "{([(<{}[<>[]}>{[]{[(<()>" }.is_corrupted());
        REQUIRE(!day10::chunk{ "[({(<(())[]>[[{[]{<()<>>" }.is_corrupted());
    }

    SECTION("illegal_char")
    {
        REQUIRE(
            *day10::chunk{ "{([(<{}[<>[]}>{[]{[(<()>" }.illegal_char() == '}');
    }

    SECTION("Part 1") { REQUIRE(day10::part1(input) == 26397); }

    SECTION("Part 2") { REQUIRE(day10::part2(input) == 0); }
}
