#include "day15.hpp"

#include "print.hpp"

#include <cassert>
#include <limits>
#include <queue>
#include <sstream>
#include <string>

namespace day15 {
using ::operator<<;

repeated_matrix::repeated_matrix(matrix<uint64_t> matrix, int repetitions)
    : matrix_{ std::move(matrix) }
    , repetitions_{ repetitions }
{}

auto repeated_matrix::get(int i, int j) const -> uint64_t
{
    int increase = 0;
    if (j > matrix_.columns(i)) {
        j = j / repetitions_;
        increase += j % repetitions_;
    }
    if (i > matrix_.rows()) {
        i = i / repetitions_;
        increase += i % repetitions_;
    }
    return (matrix_.get(i, j) + increase) % 10;
}

void repeated_matrix::set(int i, int j, uint64_t v)
{
    assert(i < matrix_.rows() && j < matrix_.columns(i));
    matrix_.set(i, j, v);
}

auto repeated_matrix::rows() const -> int
{
    return matrix_.rows() * repetitions_;
}

auto repeated_matrix::columns(int row) const -> int
{
    return matrix_.columns(row) * repetitions_;
}

std::ostream& operator<<(std::ostream& out, const repeated_matrix& matrix)
{
    return out << "repeated_matrix { " << matrix.matrix_ << ", "
               << matrix.repetitions_ << " }";
}

cavern::cavern(matrix<uint64_t> heightmap, int repetitions)
    : heightmap_{ std::move(heightmap), repetitions }
{}

auto cavern::lowest_risk_path() const -> uint64_t
{
    matrix<uint64_t> total_risk;
    std::set<std::pair<int, int>> unvisited;
    for (int i = 0; i < heightmap_.rows(); ++i) {
        for (int j = 0; j < heightmap_.columns(i); ++j) {
            total_risk.set(i, j, std::numeric_limits<uint64_t>::max());
            unvisited.emplace(i, j);
        }
    }
    total_risk.set(0, 0, 0);

    const auto follow_neighbor = [&](auto p, int i, int j) {
        if (i < 0 || j < 0 || i >= heightmap_.rows() ||
            j >= heightmap_.columns(i)) {
            return;
        }
        if (unvisited.contains({ i, j })) {
            const auto risk =
                total_risk.get(p.first, p.second) + heightmap_.get(i, j);
            total_risk.set(i, j, std::min(total_risk.get(i, j), risk));
        }
    };

    while (!unvisited.empty()) {
        const auto it = std::min_element(
            unvisited.begin(), unvisited.end(), [&](auto lhs, auto rhs) {
                return total_risk.get(lhs.first, lhs.second) <
                       total_risk.get(rhs.first, rhs.second);
            });
        const auto p = *it;
        unvisited.erase(it);
        follow_neighbor(p, p.first - 1, p.second);
        follow_neighbor(p, p.first + 1, p.second);
        follow_neighbor(p, p.first, p.second - 1);
        follow_neighbor(p, p.first, p.second + 1);
    }

    return total_risk.get(
        heightmap_.rows() - 1, heightmap_.columns(heightmap_.rows() - 1) - 1);
}

std::ostream& operator<<(std::ostream& out, const cavern& cavern)
{
    return out << "cavern { " << cavern.heightmap_ << " }";
}

auto parse(std::string_view input, int repetitions) -> cavern
{
    std::istringstream iss{ std::string{ input } };
    std::string line;
    matrix<uint64_t> heightmap;
    int row = 0;
    while (std::getline(iss, line)) {
        std::istringstream lss{ line };
        int column = 0;
        while (lss.good()) {
            char n = -1;
            lss >> n;
            if (n != -1) {
                heightmap.set(row, column++, n - '0');
            }
        }
        row++;
    }
    return cavern{ std::move(heightmap), repetitions };
}

auto part1(std::string_view input) -> uint64_t
{
    return parse(input, 1).lowest_risk_path();
}

auto part2(std::string_view input) -> uint64_t
{
    return parse(input, 5).lowest_risk_path();
}

} // namespace day15
