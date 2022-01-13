#ifndef AOC_DAY7_HPP
#define AOC_DAY7_HPP

#include <compare>
#include <string_view>
#include <vector>

namespace day7 {

struct crabs
{
    explicit crabs(std::vector<int> positions);

    void burn_rate_increase(int value);
    [[nodiscard]] auto fuel_cost() const -> int;

    auto operator==(const crabs&) const -> bool = default;

  private:
    void update_fuel_cost_per_distance();

    std::vector<int> positions_;
    int burn_rate_increase_;
    std::vector<int> fuel_cost_per_distance_;
};

auto parse(std::string_view input) -> crabs;
auto part1(std::string_view input) -> int;
auto part2(std::string_view input) -> int;

} // namespace day7

#endif
