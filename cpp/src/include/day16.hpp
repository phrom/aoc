#ifndef AOC_DAY16_HPP
#define AOC_DAY16_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <memory>
#include <string_view>
#include <vector>

struct bitstream;

namespace day16 {

using boost::multiprecision::uint128_t;

using subpackets = std::vector<std::unique_ptr<struct packet>>;

struct packet
{
    explicit packet(uint64_t version);
    virtual ~packet() = default;

    [[nodiscard]] virtual auto get_value() const -> uint128_t = 0;
    [[nodiscard]] virtual auto get_subpackets() const -> const subpackets& = 0;
    virtual auto print(std::ostream&) const -> std::ostream& = 0;

    [[nodiscard]] auto get_version() const -> uint64_t;
    [[nodiscard]] auto get_version_sum() const -> uint128_t;

  private:
    uint64_t version_;
};

struct literal_packet : packet
{
    literal_packet(uint64_t version, uint64_t value);

    [[nodiscard]] auto get_value() const -> uint128_t override;
    [[nodiscard]] auto get_subpackets() const -> const subpackets& override;
    auto print(std::ostream&) const -> std::ostream& override;

  private:
    uint64_t value_;
};

struct operator_packet : packet
{
    operator_packet(uint64_t version, subpackets subpackets);
    operator_packet(operator_packet&&) noexcept = default;

    [[nodiscard]] auto get_subpackets() const -> const subpackets& override;

  protected:
    auto print(std::ostream&, std::string_view name) const -> std::ostream&;

  private:
    subpackets subpackets_;
};

struct sum_packet : operator_packet
{
    sum_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint128_t override;
    [[nodiscard]] auto print(std::ostream&) const -> std::ostream& override;
};

struct product_packet : operator_packet
{
    product_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint128_t override;
    [[nodiscard]] auto print(std::ostream&) const -> std::ostream& override;
};

struct minimum_packet : operator_packet
{
    minimum_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint128_t override;
    [[nodiscard]] auto print(std::ostream&) const -> std::ostream& override;
};

struct maximum_packet : operator_packet
{
    maximum_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint128_t override;
    [[nodiscard]] auto print(std::ostream&) const -> std::ostream& override;
};

struct greater_than_packet : operator_packet
{
    greater_than_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint128_t override;
    [[nodiscard]] auto print(std::ostream&) const -> std::ostream& override;
};

struct less_than_packet : operator_packet
{
    less_than_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint128_t override;
    [[nodiscard]] auto print(std::ostream&) const -> std::ostream& override;
};

struct equal_to_packet : operator_packet
{
    equal_to_packet(uint64_t version, subpackets subpackets);
    [[nodiscard]] auto get_value() const -> uint128_t override;
    [[nodiscard]] auto print(std::ostream&) const -> std::ostream& override;
};

auto parse(std::string_view input) -> std::unique_ptr<packet>;
auto part1(std::string_view input) -> uint128_t;
auto part2(std::string_view input) -> uint128_t;

} // namespace day16

#endif
