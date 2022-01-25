#ifndef AOC_DAY15_HPP
#define AOC_DAY15_HPP

#include <string_view>

#include "matrix.hpp"

namespace day15 {

struct cavern
{
    explicit cavern(matrix<uint64_t> heightmap);

    [[nodiscard]] auto lowest_risk_path() const -> uint64_t;

    auto operator==(const cavern&) const -> bool = default;

  private:
    friend std::ostream& operator<<(std::ostream& out, const cavern&);
    matrix<uint64_t> heightmap_;
};

auto parse(std::string_view input) -> cavern;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day15

#endif
