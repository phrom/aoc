#ifndef AOC_DAY7_HPP
#define AOC_DAY7_HPP

#include <compare>
#include <string_view>
#include <vector>

namespace day7 {

struct crabs
{
    explicit crabs(std::vector<uint64_t> positions);

    void burn_rate_increase(uint64_t value);
    [[nodiscard]] auto fuel_cost() const -> uint64_t;

    auto operator==(const crabs&) const -> bool = default;

  private:
    void update_fuel_cost_per_distance();

    std::vector<uint64_t> positions_;
    uint64_t burn_rate_increase_;
    std::vector<uint64_t> fuel_cost_per_distance_;
};

auto parse(std::string_view input) -> crabs;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day7

#endif
