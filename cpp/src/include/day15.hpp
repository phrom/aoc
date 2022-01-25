#ifndef AOC_DAY15_HPP
#define AOC_DAY15_HPP

#include <string_view>

#include "matrix.hpp"

namespace day15 {

struct repeated_matrix
{
    repeated_matrix(matrix<uint64_t> matrix, int repetitions);
    repeated_matrix(repeated_matrix&&) noexcept = default;

    [[nodiscard]] auto get(int i, int j) const -> uint64_t;
    void set(int i, int j, uint64_t v);

    [[nodiscard]] auto rows() const -> int;
    [[nodiscard]] auto columns(int row) const -> int;

    auto operator==(const repeated_matrix&) const -> bool = default;

  private:
    friend std::ostream& operator<<(std::ostream& out, const repeated_matrix&);

    matrix<uint64_t> matrix_;
    int repetitions_;
};

struct cavern
{
    cavern(matrix<uint64_t> heightmap, int repetitions);

    [[nodiscard]] auto lowest_risk_path() const -> uint64_t;

    auto operator==(const cavern&) const -> bool = default;

  private:
    friend std::ostream& operator<<(std::ostream& out, const cavern&);
    repeated_matrix heightmap_;
};

auto parse(std::string_view input, int repetitions) -> cavern;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day15

#endif
