#include "day9.hpp"

#include <iostream>
#include <sstream>
#include <string>

namespace day9 {

heightmap::heightmap(std::vector<std::vector<int>> heightmap)
    : heightmap_{ std::move(heightmap) }
{}

auto heightmap::total_risk() const -> int
{
    int total = 0;
    const auto get_or_9 = [&](int i, int j) {
        if (i < heightmap_.size() && j < heightmap_[i].size()) {
            return heightmap_[i][j];
        }
        return 9;
    };
    for (int i = 0; i < heightmap_.size(); ++i) {
        for (int j = 0; j < heightmap_[i].size(); ++j) {
            if (heightmap_[i][j] < get_or_9(i - 1, j) &&
                heightmap_[i][j] < get_or_9(i, j - 1) &&
                heightmap_[i][j] < get_or_9(i + 1, j) &&
                heightmap_[i][j] < get_or_9(i, j + 1)) {
                total += heightmap_[i][j] + 1;
            }
        }
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
    return 0;
}

} // namespace day9
