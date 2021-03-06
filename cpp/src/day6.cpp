#include "day6.hpp"

#include <numeric>
#include <sstream>

namespace day6 {

school::school(std::vector<uint64_t> fish)
    : fish_{ 0 }
{
    for (auto f : fish) {
        fish_[f]++;
    }
}

void school::advance_day()
{
    auto zero = fish_[0];
    std::rotate(fish_.begin(), fish_.begin() + 1, fish_.end());
    fish_[6] += zero;
}

auto school::fish_count() const -> uint64_t
{
    return std::accumulate(fish_.begin(), fish_.end(), uint64_t{ 0 });
}

auto parse(std::string_view input) -> school
{
    std::istringstream iss{ std::string{ input } };
    std::vector<uint64_t> fish;
    while (!iss.eof()) {
        uint64_t interval;
        char comma;
        iss >> interval >> comma;
        fish.push_back(interval);
    }
    return school{ fish };
}

auto simulate_interval(std::string_view input, int days) -> uint64_t
{
    auto school = parse(input);
    for (int i = 0; i < days; ++i) {
        school.advance_day();
    }
    return school.fish_count();
}

auto part1(std::string_view input) -> uint64_t
{
    return simulate_interval(input, 80);
}

auto part2(std::string_view input) -> uint64_t
{
    return simulate_interval(input, 256);
}

} // namespace day6
