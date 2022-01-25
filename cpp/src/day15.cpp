#include "day15.hpp"

#include "ordered_vector.hpp"
#include "print.hpp"

#include <cassert>
#include <cstddef>
#include <limits>
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
    if (i >= matrix_.rows()) {
        int row_shift = i / matrix_.rows();
        assert(row_shift < repetitions_);
        i %= matrix_.rows();
        increase += row_shift;
    }
    if (j >= matrix_.columns(i)) {
        int column_shift = j / matrix_.columns(i);
        assert(column_shift < repetitions_);
        j %= matrix_.columns(i);
        increase += column_shift;
    }
    const auto add = matrix_.get(i, j) + increase;
    return add > 9 ? (add % 10) + 1 : add;
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
    return matrix_.columns(row % matrix_.rows()) * repetitions_;
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
    total_risk.reserve(heightmap_.rows(), heightmap_.columns(0));

    matrix<bool> visited;
    visited.reserve(heightmap_.rows(), heightmap_.columns(0));

    const auto comparison = [&](const auto& lhs, const auto& rhs) {
        const auto risk1 = total_risk.get(lhs.first, lhs.second);
        const auto risk2 = total_risk.get(rhs.first, rhs.second);
        return risk1 < risk2 || (risk1 == risk2 && lhs < rhs);
    };
    ordered_vector<std::pair<int, int>, decltype(comparison)> ordered{
        comparison
    };

    for (int i = 0; i < heightmap_.rows(); ++i) {
        for (int j = 0; j < heightmap_.columns(i); ++j) {
            total_risk.set(i, j, std::numeric_limits<uint64_t>::max());
            visited.set(i, j, false);
        }
    }
    total_risk.set(0, 0, 0);
    ordered.push({ 0, 0 });

    const auto follow_neighbor = [&](auto p, int i, int j) {
        if (i < 0 || j < 0 || i >= heightmap_.rows() ||
            j >= heightmap_.columns(i)) {
            return;
        }
        if (!visited.get(i, j)) {
            const auto risk =
                total_risk.get(p.first, p.second) + heightmap_.get(i, j);
            total_risk.set(i, j, std::min(total_risk.get(i, j), risk));
            ordered.push({ i, j });
        }
    };

    while (!ordered.empty()) {
        const auto p = ordered.front();
        ordered.erase(ordered.begin());
        if (visited.get(p.first, p.second)) {
            continue;
        }
        visited.set(p.first, p.second, true);
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
