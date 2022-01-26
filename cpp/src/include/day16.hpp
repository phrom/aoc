#ifndef AOC_DAY16_HPP
#define AOC_DAY16_HPP

#include <string_view>
#include <variant>
#include <vector>

struct bitstream;

namespace day16 {

struct literal_packet
{
    explicit literal_packet(uint64_t value);

    [[nodiscard]] auto get_value() const -> uint64_t;

  private:
    friend auto operator<<(std::ostream&, const literal_packet&)
        -> std::ostream&;
    uint64_t value_;
};

struct operator_packet
{
    using subpackets = std::vector<struct packet>;
    explicit operator_packet(subpackets subpackets);
    operator_packet(operator_packet&&) noexcept = default;

    [[nodiscard]] auto get_version_sum() const -> uint64_t;

  private:
    friend auto operator<<(std::ostream&, const operator_packet&)
        -> std::ostream&;
    subpackets subpackets_;
};

struct packet
{
    packet(uint64_t version, literal_packet value);
    packet(uint64_t version, operator_packet value);

    [[nodiscard]] auto get_version_sum() const -> uint64_t;

  private:
    friend auto operator<<(std::ostream&, const packet&) -> std::ostream&;
    uint64_t version_;
    std::variant<literal_packet, operator_packet> value_;
};

auto parse(std::string_view input) -> packet;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day16

#endif
