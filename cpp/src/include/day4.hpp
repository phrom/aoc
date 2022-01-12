#ifndef AOC_DAY4_HPP
#define AOC_DAY4_HPP

#include <array>
#include <string_view>
#include <vector>

namespace day4 {

using board = std::array<std::array<int, 5>, 5>;

struct game
{
    std::vector<int> numbers;
    std::vector<board> boards;
};

auto parse(std::string_view input) -> game;
auto part1(std::string_view input) -> int;
auto part2(std::string_view input) -> int;

} // namespace day4

#endif
