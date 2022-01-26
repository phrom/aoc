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
            octopus_[static_cast<uint64_t>(i)][static_cast<uint64_t>(j)]++;
            flash(flashed, i, j);
        }
    };

    auto ui = static_cast<uint64_t>(i);
    auto uj = static_cast<uint64_t>(j);
    if (octopus_[ui][uj] > 9 && !flashed[ui][uj]) {
        flashed[ui][uj] = true;
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

auto cavern::update() -> uint64_t
{
    for (uint64_t i = 0; i < 10; ++i) {
        for (uint64_t j = 0; j < 10; ++j) {
            octopus_[i][j]++;
        }
    }

    std::array<std::array<bool, 10>, 10> flashed{};
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            flash(flashed, i, j);
        }
    }

    uint64_t result = 0;
    for (uint64_t i = 0; i < 10; ++i) {
        for (uint64_t j = 0; j < 10; ++j) {
            if (flashed[i][j]) {
                octopus_[i][j] = 0;
                flashes_++;
                result++;
            }
        }
    }
    return result;
}

auto cavern::flashes() const -> uint64_t
{
    return flashes_;
}

auto parse(std::string_view input) -> cavern
{
    std::istringstream iss{ std::string{ input } };
    std::string line;
    std::array<std::array<uint64_t, 10>, 10> octopus;
    uint64_t row = 0;
    while (std::getline(iss, line)) {
        std::istringstream lss{ line };
        uint64_t column = 0;
        while (lss.good()) {
            unsigned char c = 0;
            lss >> c;
            if (c != 0) {
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
    auto cavern = parse(input);
    uint64_t step = 1;
    while (cavern.update() != 100) {
        step++;
    }
    return step;
}

} // namespace day11
