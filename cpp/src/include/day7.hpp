#ifndef AOC_DAY7_HPP
#define AOC_DAY7_HPP

#include <compare>
#include <string_view>
#include <vector>

namespace day7 {

struct crabs
{
    explicit crabs(std::vector<int> positions);

    [[nodiscard]] auto fuel_cost() const -> int;

    auto operator==(const crabs&) const -> bool = default;

  private:
    std::vector<int> positions_;
};

auto parse(std::string_view input) -> crabs;
auto part1(std::string_view input) -> int;
auto part2(std::string_view input) -> int;

} // namespace day7

#endif
