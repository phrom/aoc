#ifndef AOC_DAY16_HPP
#define AOC_DAY16_HPP

#include <memory>
#include <string_view>
#include <vector>

struct bitstream;

namespace day16 {

using subpackets = std::vector<std::unique_ptr<struct packet>>;

struct packet
{
    explicit packet(uint64_t version);
    virtual ~packet() = default;

    [[nodiscard]] virtual auto get_value() const -> uint64_t = 0;
    [[nodiscard]] virtual auto get_subpackets() const -> const subpackets& = 0;

    [[nodiscard]] auto get_version() const -> uint64_t;
    [[nodiscard]] auto get_version_sum() const -> uint64_t;

  private:
    friend auto operator<<(std::ostream&, const packet&) -> std::ostream&;
    uint64_t version_;
};

struct literal_packet : packet
{
    literal_packet(uint64_t version, uint64_t value);

    [[nodiscard]] auto get_value() const -> uint64_t override;
    [[nodiscard]] auto get_subpackets() const -> const subpackets& override;

  private:
    friend auto operator<<(std::ostream&, const literal_packet&)
        -> std::ostream&;
    uint64_t value_;
};

struct operator_packet : packet
{
    operator_packet(uint64_t version, subpackets subpackets);
    operator_packet(operator_packet&&) noexcept = default;

    [[nodiscard]] auto get_subpackets() const -> const subpackets& override;

  private:
    friend auto operator<<(std::ostream&, const operator_packet&)
        -> std::ostream&;
    subpackets subpackets_;
};

struct sum_packet : operator_packet
{
    sum_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint64_t override;
};

struct product_packet : operator_packet
{
    product_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint64_t override;
};

struct minimum_packet : operator_packet
{
    minimum_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint64_t override;
};

struct maximum_packet : operator_packet
{
    maximum_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint64_t override;
};

struct greater_than_packet : operator_packet
{
    greater_than_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint64_t override;
};

struct less_than_packet : operator_packet
{
    less_than_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint64_t override;
};

struct equal_to_packet : operator_packet
{
    equal_to_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint64_t override;
};

auto parse(std::string_view input) -> std::unique_ptr<packet>;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day16

#endif
