#ifndef AOC_DAY11_HPP
#define AOC_DAY11_HPP

#include <array>
#include <string_view>

namespace day11 {

struct cavern
{
    explicit cavern(const std::array<std::array<uint64_t, 10>, 10>& octopus);

    auto update() -> uint64_t;
    [[nodiscard]] auto flashes() const -> uint64_t;

    auto operator==(const cavern&) const -> bool = default;

  private:
    void flash(std::array<std::array<bool, 10>, 10>& flashed, int i, int j);
    std::array<std::array<uint64_t, 10>, 10> octopus_;
    uint64_t flashes_;
};

auto parse(std::string_view input) -> cavern;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day11

#endif
