#include <catch2/catch.hpp>

#include "day16.hpp"

TEST_CASE("Day 16: Packet Decoder")
{
    SECTION("Part 1")
    {
        REQUIRE(day16::part1("8A004A801A8002F478") == 16);
        REQUIRE(day16::part1("620080001611562C8802118E34") == 12);
        REQUIRE(day16::part1("C0015000016115A2E0802F182340") == 23);
        REQUIRE(day16::part1("A0016C880162017C3686B18A3D4780") == 31);
    }
}
