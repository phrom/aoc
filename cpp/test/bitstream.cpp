#include <catch2/catch.hpp>

#include "bitstream.hpp"

TEST_CASE("bitstream")
{
    SECTION("bitmask")
    {
        REQUIRE(bitstream::bitmask(1) == 1);
        REQUIRE(bitstream::bitmask(2) == 0b11);
        REQUIRE(bitstream::bitmask(3) == 0b111);
        REQUIRE(bitstream::bitmask(4) == 0b1111);
        REQUIRE(bitstream::bitmask(5) == 0b11111);
        REQUIRE(bitstream::bitmask(6) == 0b111111);
        REQUIRE(bitstream::bitmask(7) == 0b1111111);
        REQUIRE(bitstream::bitmask(8) == 0b11111111);
    }

    SECTION("read - single char")
    {
        auto bs = bitstream{ "A" };
        REQUIRE(bs.read(2) == 2);
        REQUIRE(bs.read(2) == 2);
    }

    SECTION("read - multiple chars, read crossing char border")
    {
        auto bs = bitstream{ "BC" };
        REQUIRE(bs.read(3) == 0b101);
        REQUIRE(bs.read(5) == 0b11100);
    }

    SECTION("from examples - literal value")
    {
        auto bs = bitstream{ "D2FE28" };
        REQUIRE(bs.read(3) == 0b110);
        REQUIRE(bs.read(3) == 0b100);
        REQUIRE(bs.read(5) == 0b10111);
        REQUIRE(bs.read(5) == 0b11110);
        REQUIRE(bs.read(5) == 0b00101);
        REQUIRE(bs.read(3) == 0b000);
    }

    SECTION("from examples - operator packet")
    {
        auto bs = bitstream{ "38006F45291200" };
        REQUIRE(bs.read(3) == 0b001);
        REQUIRE(bs.read(3) == 0b110);
        REQUIRE(bs.read(1) == 0b0);
        REQUIRE(bs.read(15) == 0b000000000011011);
        REQUIRE(bs.read(11) == 0b11010001010);
        REQUIRE(bs.read(16) == 0b0101001000100100);
        REQUIRE(bs.read(7) == 0b0000000);
    }

    SECTION("from examples - operator packet 2")
    {
        auto bs = bitstream{ "EE00D40C823060" };
        REQUIRE(bs.read(3) == 0b111);
        REQUIRE(bs.read(3) == 0b011);
        REQUIRE(bs.read(1) == 0b1);
        REQUIRE(bs.read(11) == 0b00000000011);
        REQUIRE(bs.read(11) == 0b01010000001);
        REQUIRE(bs.read(11) == 0b10010000010);
        REQUIRE(bs.read(11) == 0b00110000011);
        REQUIRE(bs.read(5) == 0b00000);
    }
}
