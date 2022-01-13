#include "day7.hpp"

#include <sstream>

namespace day7 {

crabs::crabs(std::vector<int> positions)
    : positions_{ std::move(positions) }
{}

auto crabs::fuel_cost() const -> int
{
    const auto max = *std::max_element(positions_.begin(), positions_.end());
    std::vector<int> distances;
    distances.resize(max);
    for (int i = 0; i < max; ++i) {
        for (auto position : positions_) {
            distances[i] += abs(position - i);
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
    return 0;
}

} // namespace day7
