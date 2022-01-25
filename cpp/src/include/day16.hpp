#ifndef AOC_DAY16_HPP
#define AOC_DAY16_HPP

#include <string_view>

namespace day16 {

#pragma pack(push, r1, 1)
struct packet_header
{
    unsigned int version : 3;
    unsigned int header_type_id : 3;
};

struct literal_packet
{
    bool has_next : 1;
    unsigned char bits : 4;
};

struct operator_packet
{
    enum class length_type
    {
        total_length = 0,
        number_of_subpackets = 1
    } length_type : 1;

    union
    {
        unsigned int total_length : 15;
        unsigned int number_of_subpackets : 11;
    };

    unsigned char* subpackets;
};

struct packet
{
    packet_header header;
    union
    {
        literal_packet* lit;
        operator_packet* op;
    };
};
#pragma pack(pop)

struct transmission
{};

auto parse(std::string_view input) -> transmission;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day16

#endif
