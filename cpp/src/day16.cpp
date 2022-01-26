#include "day16.hpp"

#include "bitstream.hpp"
#include "defer.hpp"
#include "print.hpp"

#include <algorithm>
#include <numeric>
#include <sstream>
#include <string>

namespace day16 {
using ::operator<<;

literal_packet::literal_packet(uint64_t value)
    : value_{ value }
{}

auto literal_packet::get_value() const -> uint64_t
{
    return value_;
}

auto operator<<(std::ostream& out, const literal_packet& packet)
    -> std::ostream&
{
    return out << "literal_packet { " << packet.value_ << " }";
}

operator_packet::operator_packet(subpackets subpackets)
    : subpackets_{ std::move(subpackets) }
{}

auto operator_packet::get_version_sum() const -> uint64_t
{
    return std::accumulate(
        subpackets_.begin(),
        subpackets_.end(),
        0U,
        [](uint64_t total, const packet& packet) {
            return total + packet.get_version_sum();
        });
}

auto operator<<(std::ostream& out, const operator_packet& packet)
    -> std::ostream&
{
    return out << "operator_packet { " << packet.subpackets_ << " }";
}

packet::packet(uint64_t version, literal_packet value)
    : version_{ version }
    , value_{ value }
{}

packet::packet(uint64_t version, operator_packet value)
    : version_{ version }
    , value_{ std::move(value) }
{}

auto packet::get_version_sum() const -> uint64_t
{
    uint64_t version_sum = version_;
    if (std::holds_alternative<operator_packet>(value_)) {
        version_sum += std::get<operator_packet>(value_).get_version_sum();
    }
    return version_sum;
}

auto operator<<(std::ostream& out, const packet& packet) -> std::ostream&
{
    return out << "packet { " << packet.version_ << ", " << packet.value_
               << " }";
}

auto parse(bitstream& bss, uint64_t* bits_read = nullptr) -> packet
{
    const auto read = [&](int b) {
        if (bits_read != nullptr) {
            *bits_read += b;
        }
        return bss.read(b);
    };
    uint64_t version = read(3);
    uint64_t type_id = read(3);
    if (type_id == 4) {
        uint64_t has_next = 0;
        uint64_t value = 0;
        do {
            has_next = read(1);
            value <<= 4;
            value |= read(4);
        } while (has_next != 0U);
        return packet{ version, literal_packet{ value } };
    }
    uint64_t length_type_id = read(1);
    std::vector<packet> subpackets;
    uint64_t total_length = 0;
    if (length_type_id == 0) {
        total_length = read(15);
        uint64_t to_read = total_length;
        while (to_read != 0U) {
            uint64_t subpacket_length = 0;
            subpackets.emplace_back(parse(bss, &subpacket_length));
            to_read -= subpacket_length;
        }
    } else {
        uint64_t number_of_subpackets = read(11);
        subpackets.reserve(number_of_subpackets);
        for (auto i = 0; i < number_of_subpackets; ++i) {
            uint64_t subpacket_length = 0;
            subpackets.emplace_back(parse(bss, &subpacket_length));
            total_length += subpacket_length;
        }
    }
    if (bits_read != nullptr) {
        *bits_read += total_length;
    }
    return packet{ version, operator_packet{ std::move(subpackets) } };
}

auto parse(std::string_view input) -> packet
{
    std::istringstream iss{ std::string{ input } };
    std::string line;
    std::getline(iss, line);
    bitstream bss{ std::move(line) };
    return parse(bss);
}

auto part1(std::string_view input) -> uint64_t
{
    return parse(input).get_version_sum();
}

auto part2(std::string_view input) -> uint64_t
{
    return 0;
}

} // namespace day16
