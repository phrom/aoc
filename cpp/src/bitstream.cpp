#include "bitstream.hpp"

#include <algorithm>
#include <iostream>

auto read_hex(unsigned char c) -> int
{
    switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'A':
        case 'a':
            return 10;
        case 'B':
        case 'b':
            return 11;
        case 'C':
        case 'c':
            return 12;
        case 'D':
        case 'd':
            return 13;
        case 'E':
        case 'e':
            return 14;
        case 'F':
        case 'f':
            return 15;
    };
    return -1;
};

auto bitstream::bitmask(int bits) -> int
{
    if (bits == 0) {
        return 0;
    }
    return (bitmask(bits - 1) << 1) | 1;
}

bitstream::bitstream(std::string input)
    : input_{ std::move(input) }
    , char_{ 0 }
    , bit_{ 0 }
{}

auto bitstream::read(uint64_t bits) -> uint64_t
{
    uint64_t result = 0;
    while (bits != 0) {
        uint64_t to_read = std::min(bits, 4 - bit_);
        result <<= to_read;
        int shift = 4 - bit_ - to_read;
        result |=
            (read_hex(input_[char_]) & (bitmask(to_read) << shift)) >> shift;
        bits -= to_read;
        bit_ += to_read;
        if (bit_ == 4) {
            char_++;
            bit_ = 0;
        }
    }
    return result;
}
