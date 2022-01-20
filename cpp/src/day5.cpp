#include "day5.hpp"

#include "print.hpp"

#include <sstream>

namespace day5 {

using ::operator<<;

point::point(int x_, int y_)
    : x{ x_ }
    , y{ y_ }
{}

auto operator<<(std::ostream& out, const point& point) -> std::ostream&
{
    return out << "point { " << point.x << ", " << point.y << " }";
}

line::line(const point& p1_, const point& p2_)
    : p1{ p1_ }
    , p2{ p2_ }
{}

auto operator<<(std::ostream& out, const line& line) -> std::ostream&
{
    return out << "line { " << line.p1 << ", " << line.p2 << " }";
}

auto line::is_horizontal() const -> bool
{
    return p1.x == p2.x;
}

auto line::is_vertical() const -> bool
{
    return p1.y == p2.y;
}

auto line::points() const -> std::vector<point>
{
    std::vector<point> result;
    const auto delta = [](int a, int b) {
        const int diff = b - a;
        return diff == 0 ? 0 : diff > 0 ? 1 : -1;
    };
    const int dx = delta(p1.x, p2.x);
    const int dy = delta(p1.y, p2.y);
    point p = p1;
    while (p != p2) {
        result.emplace_back(p);
        p.x += dx;
        p.y += dy;
    }
    result.emplace_back(p2);
    return result;
}

auto operator<<(std::ostream& out, const matrix& matrix) -> std::ostream&
{
    out << "matrix { ";
    for (const auto& r : matrix.value_) {
        out << r << "\n";
    }
    return out << "}";
}

auto matrix::size() const -> std::pair<int, int>
{
    const auto compare_size = [](const auto& lhs, const auto& rhs) {
        return lhs.size() < rhs.size();
    };
    return {
        value_.size(),
        std::max_element(value_.begin(), value_.end(), compare_size)->size()
    };
}

auto matrix::get(int x, int y) const -> int
{
    if (!(x < value_.size() && y < value_[x].size())) {
        return 0;
    }
    return value_[x][y];
}

template<typename T>
void ensure_size(std::vector<T>& vec, int size)
{
    if (vec.size() < size) {
        vec.resize(size);
    }
}

void matrix::set(int x, int y, int value)
{
    ensure_size(value_, x + 1);
    ensure_size(value_[x], y + 1);
    value_[x][y] = value;
}

floor::floor(std::vector<line> lines)
    : lines_{ std::move(lines) }
{}

auto floor::overlapping_points(bool include_diagonals) const -> int
{
    int total = 0;
    const matrix overlaps = calculate_overlap(include_diagonals);
    const auto size = overlaps.size();
    for (int i = 0; i < size.first; ++i) {
        for (int j = 0; j < size.second; ++j) {
            if (overlaps.get(i, j) > 1) {
                total++;
            }
        }
    }
    return total;
}

auto floor::calculate_overlap(bool include_diagonals) const -> matrix
{
    matrix result;
    for (const auto& line : lines_) {
        if (line.is_horizontal() || line.is_vertical() || include_diagonals) {
            for (auto point : line.points()) {
                result.set(point.x, point.y, result.get(point.x, point.y) + 1);
            }
        }
    }
    return result;
}

auto parse(std::string_view input) -> floor
{
    std::istringstream iss{ std::string{ input } };
    std::vector<line> lines;
    std::string l;
    while (std::getline(iss, l)) {
        int x1, y1, x2, y2;
        char comma;
        std::string arrow;
        std::istringstream lss{ l };
        lss >> x1 >> comma >> y1 >> arrow >> x2 >> comma >> y2;
        lines.emplace_back(point{ x1, y1 }, point{ x2, y2 });
    }
    return floor{ lines };
}

auto part1(std::string_view input) -> int
{
    return parse(input).overlapping_points(false);
}

auto part2(std::string_view input) -> int
{
    return parse(input).overlapping_points(true);
}

} // namespace day5
