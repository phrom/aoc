#include "day15.hpp"

#include "print.hpp"

#include <algorithm>
#include <limits>
#include <queue>
#include <sstream>
#include <string>

namespace day15 {
using ::operator<<;

cavern::cavern(matrix<uint64_t> heightmap)
    : heightmap_{ std::move(heightmap) }
{}

auto cavern::lowest_risk_path() const -> uint64_t
{
    struct comparison
    {
        explicit comparison(const matrix<uint64_t>& total_risk_)
            : total_risk{ total_risk_ }
        {}
        auto operator()(
            const std::pair<int, int>& lhs,
            const std::pair<int, int>& rhs) -> bool
        {
            return total_risk.get(lhs.first, lhs.second) <
                   total_risk.get(rhs.first, rhs.second);
        }

      private:
        const matrix<uint64_t>& total_risk;
    };

    matrix<uint64_t> total_risk;
    matrix<bool> unvisited;

    std::vector<std::pair<int, int>> ordered;
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>::iterator>
        ordered_it;

    for (int i = 0; i < heightmap_.rows(); ++i) {
        for (int j = 0; j < heightmap_.columns(i); ++j) {
            total_risk.set(i, j, std::numeric_limits<uint64_t>::max());
            unvisited.set(i, j, true);
            ordered_it[{ i, j }] = ordered.insert(
                std::lower_bound(
                    ordered.begin(),
                    ordered.end(),
                    std::pair{ i, j },
                    comparison{ total_risk }),
                { i, j });
        }
    }
    total_risk.set(0, 0, 0);

    const auto follow_neighbor = [&](auto p, int i, int j) {
        if (i < 0 || j < 0 || i >= heightmap_.rows() ||
            j >= heightmap_.columns(i)) {
            return;
        }
        if (unvisited.get(i, j)) {
            const auto risk =
                total_risk.get(p.first, p.second) + heightmap_.get(i, j);
            total_risk.set(i, j, std::min(total_risk.get(i, j), risk));
            auto oit = ordered_it.find({ i, j });
            ordered.erase(oit->second);
            oit->second = ordered.insert(
                std::lower_bound(
                    ordered.begin(),
                    ordered.end(),
                    std::pair{ i, j },
                    comparison{ total_risk }),
                { i, j });
        }
    };

    while (!ordered.empty()) {
        const auto p = ordered.front();
        ordered.erase(ordered.begin());
        unvisited.set(p.first, p.second, false);
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

auto parse(std::string_view input) -> cavern
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
    return cavern{ std::move(heightmap) };
}

auto part1(std::string_view input) -> uint64_t
{
    return parse(input).lowest_risk_path();
}

auto part2(std::string_view input) -> uint64_t
{
    return 0;
}

} // namespace day15
