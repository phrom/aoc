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

literal_packet::literal_packet(uint64_t version, uint64_t value)
    : packet{ version }
    , value_{ value }
{}

auto literal_packet::get_value() const -> uint64_t
{
    return value_;
}

auto literal_packet::get_subpackets() const -> const subpackets&
{
    static const subpackets empty{};
    return empty;
}

auto literal_packet::print(std::ostream& out) const -> std::ostream&
{
    return out << "literal_packet { " << get_version() << ", " << value_
               << " }";
}

operator_packet::operator_packet(uint64_t version, subpackets subpackets)
    : packet{ version }
    , subpackets_{ std::move(subpackets) }
{}

auto operator_packet::get_subpackets() const -> const subpackets&
{
    return subpackets_;
}

auto operator_packet::print(std::ostream& out, std::string_view name) const
    -> std::ostream&
{
    out << name << " { " << get_version() << ", [ ";
    for (const auto& subpacket : subpackets_) {
        subpacket->print(out) << ", ";
    }
    return out << " ] }";
}

packet::packet(uint64_t version)
    : version_{ version }
{}

auto packet::get_version() const -> uint64_t
{
    return version_;
}

sum_packet::sum_packet(uint64_t version, subpackets subpackets)
    : operator_packet{ version, std::move(subpackets) }
{}

auto sum_packet::get_value() const -> uint64_t
{
    return std::accumulate(
        get_subpackets().begin(),
        get_subpackets().end(),
        0,
        [](uint64_t total, const auto& packet) {
            return total + packet->get_value();
        });
}

auto sum_packet::print(std::ostream& out) const -> std::ostream&
{
    return operator_packet::print(out, "sum_packet");
}

product_packet::product_packet(uint64_t version, subpackets subpackets)
    : operator_packet{ version, std::move(subpackets) }
{}

auto product_packet::get_value() const -> uint64_t
{
    return std::accumulate(
        get_subpackets().begin(),
        get_subpackets().end(),
        1,
        [](uint64_t total, const auto& packet) {
            return total * packet->get_value();
        });
}

auto product_packet::print(std::ostream& out) const -> std::ostream&
{
    return operator_packet::print(out, "product_packet");
}

minimum_packet::minimum_packet(uint64_t version, subpackets subpackets)
    : operator_packet{ version, std::move(subpackets) }
{}

auto minimum_packet::get_value() const -> uint64_t
{
    return (*std::min_element(
                get_subpackets().begin(),
                get_subpackets().end(),
                [](const auto& lhs, const auto& rhs) {
                    return lhs->get_value() < rhs->get_value();
                }))
        ->get_value();
}

auto minimum_packet::print(std::ostream& out) const -> std::ostream&
{
    return operator_packet::print(out, "minimum_packet");
}

maximum_packet::maximum_packet(uint64_t version, subpackets subpackets)
    : operator_packet{ version, std::move(subpackets) }
{}

auto maximum_packet::get_value() const -> uint64_t
{
    return (*std::max_element(
                get_subpackets().begin(),
                get_subpackets().end(),
                [](const auto& lhs, const auto& rhs) {
                    return lhs->get_value() < rhs->get_value();
                }))
        ->get_value();
}

auto maximum_packet::print(std::ostream& out) const -> std::ostream&
{
    return operator_packet::print(out, "maximum_packet");
}

greater_than_packet::greater_than_packet(
    uint64_t version,
    subpackets subpackets)
    : operator_packet{ version, std::move(subpackets) }
{}

auto greater_than_packet::get_value() const -> uint64_t
{
    return static_cast<uint64_t>(
        get_subpackets().front()->get_value() >
        get_subpackets().back()->get_value());
}

auto greater_than_packet::print(std::ostream& out) const -> std::ostream&
{
    return operator_packet::print(out, "greater_than_packet");
}

less_than_packet::less_than_packet(uint64_t version, subpackets subpackets)
    : operator_packet{ version, std::move(subpackets) }
{}

auto less_than_packet::get_value() const -> uint64_t
{
    return static_cast<uint64_t>(
        get_subpackets().front()->get_value() <
        get_subpackets().back()->get_value());
}

auto less_than_packet::print(std::ostream& out) const -> std::ostream&
{
    return operator_packet::print(out, "less_than_packet");
}

equal_to_packet::equal_to_packet(uint64_t version, subpackets subpackets)
    : operator_packet{ version, std::move(subpackets) }
{}

auto equal_to_packet::get_value() const -> uint64_t
{
    return static_cast<uint64_t>(
        get_subpackets().front()->get_value() ==
        get_subpackets().back()->get_value());
}

auto equal_to_packet::print(std::ostream& out) const -> std::ostream&
{
    return operator_packet::print(out, "equal_to_packet");
}

enum class packet_type
{
    sum = 0,
    product = 1,
    minimum = 2,
    maximum = 3,
    literal = 4,
    greater_than = 5,
    less_than = 6,
    equal_to = 7
};

auto parse(bitstream& bss, uint64_t* bits_read = nullptr)
    -> std::unique_ptr<packet>
{
    const auto read = [&](int b) {
        if (bits_read != nullptr) {
            *bits_read += b;
        }
        return bss.read(b);
    };
    uint64_t version = read(3);
    auto type_id = static_cast<packet_type>(read(3));
    if (type_id == packet_type::literal) {
        uint64_t has_next = 0;
        uint64_t value = 0;
        do {
            has_next = read(1);
            value <<= 4;
            value |= read(4);
        } while (has_next != 0U);
        return std::make_unique<literal_packet>(version, value);
    }
    uint64_t length_type_id = read(1);
    subpackets subpackets;
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
    switch (type_id) {
        case packet_type::sum:
            return std::make_unique<sum_packet>(version, std::move(subpackets));
        case packet_type::product:
            return std::make_unique<product_packet>(
                version, std::move(subpackets));
        case packet_type::minimum:
            return std::make_unique<minimum_packet>(
                version, std::move(subpackets));
        case packet_type::maximum:
            return std::make_unique<maximum_packet>(
                version, std::move(subpackets));
        case packet_type::greater_than:
            return std::make_unique<greater_than_packet>(
                version, std::move(subpackets));
        case packet_type::less_than:
            return std::make_unique<less_than_packet>(
                version, std::move(subpackets));
        case packet_type::equal_to:
            return std::make_unique<equal_to_packet>(
                version, std::move(subpackets));
        case packet_type::literal:
        default:
            exit(1);
    };
}

auto parse(std::string_view input) -> std::unique_ptr<packet>
{
    std::istringstream iss{ std::string{ input } };
    std::string line;
    std::getline(iss, line);
    bitstream bss{ std::move(line) };
    return parse(bss);
}

auto get_version_sum(const packet& packet) -> uint64_t
{
    uint64_t version_sum = packet.get_version();
    for (const auto& subpacket : packet.get_subpackets()) {
        version_sum += get_version_sum(*subpacket);
    }
    return version_sum;
}

auto part1(std::string_view input) -> uint64_t
{
    return get_version_sum(*parse(input));
}

auto part2(std::string_view input) -> uint64_t
{
    return parse(input)->get_value();
}

} // namespace day16
