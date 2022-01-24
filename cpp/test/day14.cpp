#include <catch2/catch.hpp>

#include "day14.hpp"

TEST_CASE("Day 14: Extended Polymerization")
{
    const char* input = R"(NNCB

CH -> B
HH -> N
CB -> H
NH -> C
HB -> C
HC -> B
HN -> C
NN -> C
BH -> H
NC -> B
NB -> B
BN -> B
BB -> N
BC -> B
CC -> N
CN -> C
)";

    SECTION("Parse")
    {
        const auto expected = day14::manual{
            day14::polymer_template{ "NNCB" },
            std::vector<day14::pair_insertion_rule>{
                day14::pair_insertion_rule{ symbol{ "CH" }, 'B' },
                day14::pair_insertion_rule{ symbol{ "HH" }, 'N' },
                day14::pair_insertion_rule{ symbol{ "CB" }, 'H' },
                day14::pair_insertion_rule{ symbol{ "NH" }, 'C' },
                day14::pair_insertion_rule{ symbol{ "HB" }, 'C' },
                day14::pair_insertion_rule{ symbol{ "HC" }, 'B' },
                day14::pair_insertion_rule{ symbol{ "HN" }, 'C' },
                day14::pair_insertion_rule{ symbol{ "NN" }, 'C' },
                day14::pair_insertion_rule{ symbol{ "BH" }, 'H' },
                day14::pair_insertion_rule{ symbol{ "NC" }, 'B' },
                day14::pair_insertion_rule{ symbol{ "NB" }, 'B' },
                day14::pair_insertion_rule{ symbol{ "BN" }, 'B' },
                day14::pair_insertion_rule{ symbol{ "BB" }, 'N' },
                day14::pair_insertion_rule{ symbol{ "BC" }, 'B' },
                day14::pair_insertion_rule{ symbol{ "CC" }, 'N' },
                day14::pair_insertion_rule{ symbol{ "CN" }, 'C' } }
        };
        const auto found = day14::parse(input);
        REQUIRE(expected == found);
    }

    SECTION("Part 1") { REQUIRE(day14::part1(input) == 1588); }
    SECTION("Part 2") { REQUIRE(day14::part2(input) == 2188189693529); }
}
