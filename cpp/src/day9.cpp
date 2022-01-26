#include "day9.hpp"

#include <numeric>
#include <queue>
#include <sstream>
#include <string>

namespace day9 {

heightmap::heightmap(std::vector<std::vector<int>> heightmap)
    : heightmap_{ std::move(heightmap) }
    , flooded_{}
{}

auto heightmap::get(uint64_t i, uint64_t j) const -> int
{
    if (i < heightmap_.size() && j < heightmap_[i].size()) {
        return heightmap_[i][j];
    }
    return 9;
}

auto heightmap::total_risk() const -> int
{
    int total = 0;
    for (uint64_t i = 0; i < heightmap_.size(); ++i) {
        for (uint64_t j = 0; j < heightmap_[i].size(); ++j) {
            if (heightmap_[i][j] < get(i - 1, j) &&
                heightmap_[i][j] < get(i, j - 1) &&
                heightmap_[i][j] < get(i + 1, j) &&
                heightmap_[i][j] < get(i, j + 1)) {
                total += heightmap_[i][j] + 1;
            }
        }
    }
    return total;
}

auto heightmap::flood(uint64_t i, uint64_t j) -> int
{
    if (get(i, j) == 9 || flooded_.contains({ i, j })) {
        return 0;
    }
    flooded_.insert({ i, j });
    return 1 + flood(i - 1, j) + flood(i, j - 1) + flood(i + 1, j) +
           flood(i, j + 1);
}

auto heightmap::largest_basins() -> int
{
    std::priority_queue<int> basin_size;
    for (uint64_t i = 0; i < heightmap_.size(); ++i) {
        for (uint64_t j = 0; j < heightmap_[i].size(); ++j) {
            if (heightmap_[i][j] != 9 && !flooded_.contains({ i, j })) {
                basin_size.push(flood(i, j));
            }
        }
    }

    int total = 1;
    for (int i = 0; i < 3; ++i) {
        total *= basin_size.top();
        basin_size.pop();
    }
    return total;
}

auto parse(std::string_view input) -> heightmap
{
    std::istringstream iss{ std::string{ input } };
    std::string line;
    std::vector<std::vector<int>> result;
    while (std::getline(iss, line)) {
        std::istringstream lss{ line };
        result.emplace_back();
        while (lss.good()) {
            char number = -1;
            lss >> number;
            if (number != -1) {
                result.back().push_back(number - '0');
            }
        }
    }
    return heightmap{ result };
}

auto part1(std::string_view input) -> int
{
    return parse(input).total_risk();
}

auto part2(std::string_view input) -> int
{
    return parse(input).largest_basins();
}

} // namespace day9
