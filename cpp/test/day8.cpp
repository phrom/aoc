#include <catch2/catch.hpp>

#include "day8.hpp"
#include "read_file.hpp"

TEST_CASE("Day 8: Seven Segment Search")
{
    const char* input =
        R"(be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe
edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec | fcgedb cgb dgebacf gc
fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef | cg cg fdcagb cbg
fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega | efabcd cedba gadfec cb
aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga | gecf egdcabf bgf bfgea
fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf | gebdcfa ecba ca fadegcb
dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf | cefg dcbef fcge gbcadfe
bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd | ed bcgafe cdgba cbgef
egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg | gbdfcae bgc cg cgb
gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc | fgae cfgab fg bagce
)";

    SECTION("Part 1") { REQUIRE(day8::part1(input) == 26); }
    SECTION("Part 2") { REQUIRE(day8::part2(input) == 61229); }

    SECTION("signal difference")
    {
        REQUIRE(day8::signal_difference("acf", std::vector{ 'c', 'f' }) == 'a');
        REQUIRE(day8::signal_difference("cf", std::vector{ 'f' }) == 'c');
        REQUIRE(day8::signal_difference("bcf", std::vector{ 'c', 'f' }) == 'b');
        REQUIRE(
            day8::signal_difference("abfg", std::vector{ 'a', 'b', 'f' }) ==
            'g');
        REQUIRE(day8::signal_difference("adg", std::vector{ 'a', 'g' }) == 'd');
        REQUIRE(
            day8::signal_difference(
                "abcdefg", std::vector{ 'a', 'b', 'c', 'd', 'f', 'g' }) == 'e');
    }

    SECTION("signal intersection")
    {
        REQUIRE(day8::signal_intersection({ "abcd", "abc" }) == "abc");
        REQUIRE(
            day8::signal_intersection({ "abcefg", "abdefg", "abcdfg" }) ==
            "abfg");
        REQUIRE(
            day8::signal_intersection({ "acdeg", "acdfg", "abdfg" }) == "adg");
        REQUIRE(day8::signal_intersection({ "abfg", "cf" }) == "f");
    }

    SECTION("Full input")
    {
        const auto file = read_file("day8.txt");
        REQUIRE(day8::part1(file) == 493);
        REQUIRE(day8::part2(file) == 1010460);
    }
}
