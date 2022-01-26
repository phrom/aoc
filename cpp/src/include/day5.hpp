#ifndef AOC_DAY5_HPP
#define AOC_DAY5_HPP

#include <compare>
#include <string_view>
#include <vector>

namespace day5 {

struct point
{
    point(uint64_t x_, uint64_t y_);

    auto operator<=>(const point&) const = default;

    uint64_t x;
    uint64_t y;
};

auto operator<<(std::ostream&, const point&) -> std::ostream&;

struct line
{
    line(const point& p1_, const point& p2_);

    auto operator<=>(const line&) const = default;

    [[nodiscard]] auto is_horizontal() const -> bool;
    [[nodiscard]] auto is_vertical() const -> bool;
    [[nodiscard]] auto points() const -> std::vector<point>;

    point p1;
    point p2;
};

auto operator<<(std::ostream&, const line&) -> std::ostream&;

struct matrix
{
    [[nodiscard]] auto size() const -> std::pair<uint64_t, uint64_t>;
    [[nodiscard]] auto get(uint64_t x, uint64_t y) const -> int;
    void set(uint64_t x, uint64_t y, int value);

    auto operator<=>(const matrix&) const = default;
    friend auto operator<<(std::ostream&, const matrix&) -> std::ostream&;

  private:
    std::vector<std::vector<int>> value_;
};

struct floor
{
    explicit floor(std::vector<line> lines);

    auto operator<=>(const floor&) const = default;

    [[nodiscard]] auto overlapping_points(bool include_diagonals) const -> int;

  private:
    std::vector<line> lines_;
    [[nodiscard]] auto calculate_overlap(bool include_diagonals) const
        -> matrix;
};

auto parse(std::string_view input) -> floor;
auto part1(std::string_view input) -> int;
auto part2(std::string_view input) -> int;

} // namespace day5

#endif
