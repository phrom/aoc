#include "day17.hpp"

#include <sstream>

namespace day17 {

target_area::target_area(const range<int64_t>& x, const range<int64_t>& y)
    : x_{ x }
    , y_{ y }
{}

auto target_area::x() const -> range<int64_t>
{
    return x_;
}

auto target_area::y() const -> range<int64_t>
{
    return y_;
}

auto operator<<(std::ostream& out, const target_area& target) -> std::ostream&
{
    return out << "target_area { " << target.x_ << ", " << target.y_ << " }";
}

probe_launcher::probe_launcher(const target_area& target)
    : target_{ target }
{}

auto probe_launcher::max_y() const -> uint64_t
{
    auto velocity = static_cast<uint64_t>(std::abs(target_.y().min() + 1));
    uint64_t max_y = 0;
    for (uint64_t i = 0; i <= velocity; ++i) {
        max_y += i;
    }
    return max_y;
}

auto probe_launcher::hits_target(int64_t dx, int64_t dy, int64_t x, int64_t y)
    const -> bool
{
    if (target_.x().contains(x) && target_.y().contains(y)) {
        return true;
    }
    if (x > target_.x().max() || y < target_.y().min()) {
        return false;
    }
    x += dx;
    y += dy;
    if (dx > 0) {
        dx -= 1;
    } else if (dx < 0) {
        dx += 1;
    }
    dy -= 1;
    return hits_target(dx, dy, x, y);
}

auto probe_launcher::distinct_velocities() const -> uint64_t
{
    int64_t min_x = 0;
    for (int64_t sum = 0; !target_.x().contains(sum); sum += ++min_x) {
    }
    uint64_t count = 0;
    for (int64_t dx = min_x; dx <= target_.x().max(); ++dx) {
        for (int64_t dy = target_.y().min(); dy <= std::abs(target_.y().min());
             ++dy) {
            if (hits_target(dx, dy)) {
                count++;
            }
        }
    }
    return count;
}

auto operator<<(std::ostream& out, const probe_launcher& launcher)
    -> std::ostream&
{
    return out << "probe_launcher { " << launcher.target_ << " }";
}

auto parse(std::string_view input) -> probe_launcher
{
    std::istringstream iss{ std::string{ input } };
    std::string word;
    char c;
    int64_t min_x, max_x, min_y, max_y;
    iss >> word >> word;                            // target area:
    iss >> c >> c >> min_x >> c >> c >> max_x >> c; // x=20..30,
    iss >> c >> c >> min_y >> c >> c >> max_y >> c; // y=-10..-5
    return probe_launcher{ target_area{ { min_x, max_x }, { min_y, max_y } } };
}

auto part1(std::string_view input) -> uint64_t
{
    return parse(input).max_y();
}

auto part2(std::string_view input) -> uint64_t
{
    return parse(input).distinct_velocities();
}

} // namespace day17
