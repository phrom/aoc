#ifndef AOC_DAY6_HPP
#define AOC_DAY6_HPP

#include <array>
#include <compare>
#include <string_view>
#include <vector>

namespace day6 {

struct school
{
    explicit school(std::vector<uint64_t> fish);

    void advance_day();
    [[nodiscard]] auto fish_count() const -> uint64_t;

    auto operator==(const school&) const -> bool = default;

  private:
    std::array<uint64_t, 9> fish_;
};

auto parse(std::string_view input) -> school;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day6

#endif
