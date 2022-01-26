#include "day7.hpp"

#include <algorithm>
#include <sstream>

namespace day7 {

crabs::crabs(std::vector<uint64_t> positions)
    : positions_{ std::move(positions) }
    , burn_rate_increase_{ 0 }
    , fuel_cost_per_distance_{}
{
    update_fuel_cost_per_distance();
}

void crabs::update_fuel_cost_per_distance()
{
    if (!fuel_cost_per_distance_.empty()) {
        fuel_cost_per_distance_.clear();
    }
    const auto max = *std::max_element(positions_.begin(), positions_.end());
    fuel_cost_per_distance_.reserve(max + 1);
    uint64_t sum = 0;
    for (uint64_t i = 0; i < max + 1; ++i) {
        fuel_cost_per_distance_.push_back(sum);
        sum += 1 + i * burn_rate_increase_;
    }
}

void crabs::burn_rate_increase(uint64_t value)
{
    const bool changed = burn_rate_increase_ != value;
    burn_rate_increase_ = value;
    if (changed) {
        update_fuel_cost_per_distance();
    }
}

auto crabs::fuel_cost() const -> uint64_t
{
    std::vector<uint64_t> distances;
    distances.resize(fuel_cost_per_distance_.size());
    for (uint64_t i = 0; i < fuel_cost_per_distance_.size(); ++i) {
        for (auto position : positions_) {
            distances[i] += fuel_cost_per_distance_
                [std::max(position, i) - std::min(position, i)];
        }
    }
    return *std::min_element(distances.begin(), distances.end());
}

auto parse(std::string_view input) -> crabs
{
    std::istringstream iss{ std::string{ input } };
    std::vector<uint64_t> positions;
    while (!iss.eof()) {
        uint64_t position;
        char comma;
        iss >> position >> comma;
        positions.push_back(position);
    }
    return crabs{ positions };
}

auto part1(std::string_view input) -> uint64_t
{
    return parse(input).fuel_cost();
}

auto part2(std::string_view input) -> uint64_t
{
    auto crabs = parse(input);
    crabs.burn_rate_increase(1);
    return crabs.fuel_cost();
}

} // namespace day7
