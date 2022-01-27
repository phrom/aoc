#ifndef AOC_DAY17_HPP
#define AOC_DAY17_HPP

#include "range.hpp"

#include <string_view>

namespace day17 {

struct target_area
{
    target_area(const range<int64_t>& x, const range<int64_t>& y);

    [[nodiscard]] auto x() const -> range<int64_t>;
    [[nodiscard]] auto y() const -> range<int64_t>;

    auto operator<=>(const target_area&) const = default;

  private:
    friend auto operator<<(std::ostream&, const target_area&) -> std::ostream&;
    range<int64_t> x_;
    range<int64_t> y_;
};

struct probe_launcher
{
    explicit probe_launcher(const target_area& target);

    [[nodiscard]] auto max_y() const -> uint64_t;

    auto operator<=>(const probe_launcher&) const = default;

  private:
    friend auto operator<<(std::ostream&, const probe_launcher&)
        -> std::ostream&;
    target_area target_;
};

auto parse(std::string_view input) -> probe_launcher;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day17

#endif
