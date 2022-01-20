#ifndef AOC_DAY9_HPP
#define AOC_DAY9_HPP

#include <set>
#include <string>
#include <string_view>
#include <vector>

namespace day9 {

struct heightmap
{
    explicit heightmap(std::vector<std::vector<int>> heightmap);

    [[nodiscard]] auto total_risk() const -> int;
    [[nodiscard]] auto largest_basins() -> int;

    auto operator==(const heightmap&) const -> bool = default;

  private:
    [[nodiscard]] auto get(int i, int j) const -> int;
    [[nodiscard]] auto flood(int i, int j) -> int;
    std::vector<std::vector<int>> heightmap_;
    std::set<std::pair<int, int>> flooded_;
};

auto parse(std::string_view input) -> heightmap;
auto part1(std::string_view input) -> int;
auto part2(std::string_view input) -> int;

} // namespace day9

#endif
