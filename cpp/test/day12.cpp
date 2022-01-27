#include <catch2/catch.hpp>

#include "day12.hpp"
#include "read_file.hpp"

TEST_CASE("Day 12: Passage Pathing")
{
    const char* input = R"(fs-end
he-DX
fs-he
start-DX
pj-DX
end-zg
zg-sl
zg-pj
pj-he
RW-he
fs-DX
pj-RW
zg-RW
start-pj
he-WI
zg-he
pj-fs
start-RW
)";

    SECTION("Parse")
    {
        const auto system = day12::parse(R"(start-A
start-b
A-c
A-b
b-d
A-end
b-end
)");
        day12::cave_system expected;
        expected.add_connection(symbol{ "start" }, symbol{ "A" });
        expected.add_connection(symbol{ "start" }, symbol{ "b" });
        expected.add_connection(symbol{ "A" }, symbol{ "c" });
        expected.add_connection(symbol{ "A" }, symbol{ "b" });
        expected.add_connection(symbol{ "b" }, symbol{ "d" });
        expected.add_connection(symbol{ "A" }, symbol{ "end" });
        expected.add_connection(symbol{ "b" }, symbol{ "end" });
        REQUIRE(system == expected);
    }

    SECTION("Part 1") { REQUIRE(day12::part1(input) == 226); }

    SECTION("Part 2") { REQUIRE(day12::part2(input) == 3509); }

    SECTION("Full input")
    {
        const auto file = read_file("day12.txt");
        REQUIRE(day12::part1(file) == 4754);
        REQUIRE(day12::part2(file) == 143562);
    }
}
