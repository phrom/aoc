#include "day11.hpp"

#include <set>
#include <sstream>
#include <string>

namespace day11 {

cavern::cavern(const std::array<std::array<uint64_t, 10>, 10>& octopus)
    : octopus_{ octopus }
    , flashes_{ 0 }
{}

void cavern::flash(std::array<std::array<bool, 10>, 10>& flashed, int i, int j)
{
    const auto recur = [&](int i, int j) {
        if (i >= 0 && i < 10 && j >= 0 && j < 10) {
            octopus_[i][j]++;
            flash(flashed, i, j);
        }
    };

    if (octopus_[i][j] > 9 && !flashed[i][j]) {
        flashed[i][j] = true;
        recur(i - 1, j - 1);
        recur(i - 1, j);
        recur(i - 1, j + 1);
        recur(i, j - 1);
        recur(i, j + 1);
        recur(i + 1, j - 1);
        recur(i + 1, j);
        recur(i + 1, j + 1);
    }
}

void cavern::update()
{
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            octopus_[i][j]++;
        }
    }

    std::array<std::array<bool, 10>, 10> flashed = { false };
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            flash(flashed, i, j);
        }
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (flashed[i][j]) {
                octopus_[i][j] = 0;
                flashes_++;
            }
        }
    }
}

auto cavern::flashes() const -> int
{
    return flashes_;
}

auto parse(std::string_view input) -> cavern
{
    std::istringstream iss{ std::string{ input } };
    std::string line;
    std::array<std::array<uint64_t, 10>, 10> octopus;
    int row = 0;
    while (std::getline(iss, line)) {
        std::istringstream lss{ line };
        int column = 0;
        while (lss.good()) {
            char c = -1;
            lss >> c;
            if (c != -1) {
                octopus[row][column++] = c - '0';
            }
        }
        row++;
    }
    return cavern{ octopus };
}

auto part1(std::string_view input) -> uint64_t
{
    auto cavern = parse(input);
    for (int i = 0; i < 100; ++i) {
        cavern.update();
    }
    return cavern.flashes();
}

auto part2(std::string_view input) -> uint64_t
{
    return 0;
}

} // namespace day11
