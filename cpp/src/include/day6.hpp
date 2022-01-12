#ifndef AOC_DAY6_HPP
#define AOC_DAY6_HPP

#include <compare>
#include <string_view>
#include <vector>

namespace day6 {

struct school
{
    explicit school(std::vector<int> fish);

    void advance_day();

    auto operator==(const school&) const -> bool = default;

    std::vector<int> fish;
};

auto parse(std::string_view input) -> school;
auto part1(std::string_view input) -> int;
auto part2(std::string_view input) -> int;

} // namespace day6

#endif
