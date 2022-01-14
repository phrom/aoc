#include "day7.hpp"

#include <sstream>

namespace day7 {

crabs::crabs(std::vector<int> positions)
    : positions_{ std::move(positions) }
    , burn_rate_increase_{ 0 }
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
    int sum = 0;
    for (int i = 0; i < max + 1; ++i) {
        fuel_cost_per_distance_.push_back(sum);
        sum += 1 + i * burn_rate_increase_;
    }
}

void crabs::burn_rate_increase(int value)
{
    const bool changed = burn_rate_increase_ != value;
    burn_rate_increase_ = value;
    if (changed) {
        update_fuel_cost_per_distance();
    }
}

auto crabs::fuel_cost() const -> int
{
    std::vector<int> distances;
    distances.resize(fuel_cost_per_distance_.size());
    for (int i = 0; i < fuel_cost_per_distance_.size(); ++i) {
        for (auto position : positions_) {
            distances[i] += fuel_cost_per_distance_[abs(position - i)];
        }
    }
    return *std::min_element(distances.begin(), distances.end());
}

auto parse(std::string_view input) -> crabs
{
    std::istringstream iss{ std::string{ input } };
    std::vector<int> positions;
    while (!iss.eof()) {
        int position;
        char comma;
        iss >> position >> comma;
        positions.push_back(position);
    }
    return crabs{ positions };
}

auto part1(std::string_view input) -> int
{
    return parse(input).fuel_cost();
}

auto part2(std::string_view input) -> int
{
    auto crabs = parse(input);
    crabs.burn_rate_increase(1);
    return crabs.fuel_cost();
}

} // namespace day7
