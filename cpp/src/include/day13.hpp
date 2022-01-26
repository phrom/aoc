#ifndef AOC_DAY13_HPP
#define AOC_DAY13_HPP

#include "matrix.hpp"
#include <string_view>
#include <vector>

namespace day13 {

struct paper
{
    explicit paper(matrix<bool> paper);

    void fold(const struct instruction& instruction);
    [[nodiscard]] auto visible_dots() const -> std::vector<std::pair<int, int>>;

    auto operator==(const paper&) const -> bool = default;

  private:
    friend std::ostream& operator<<(std::ostream& out, const paper& paper);
    matrix<bool> paper_;
};

struct instruction
{
    enum class axis
    {
        x,
        y
    };

    instruction(axis axis, uint64_t coord);

    [[nodiscard]] auto get_axis() const -> axis;
    [[nodiscard]] auto get_coord() const -> uint64_t;

    auto operator==(const instruction&) const -> bool = default;

  private:
    friend std::ostream& operator<<(std::ostream& out, const instruction&);
    enum axis axis_;
    uint64_t coord_;
};

struct manual
{
    manual(paper paper, std::vector<instruction> instructions);

    [[nodiscard]] auto get_paper() -> paper&;
    [[nodiscard]] auto get_instructions() const
        -> const std::vector<instruction>&;

    auto operator==(const manual&) const -> bool = default;

  private:
    friend std::ostream& operator<<(std::ostream& out, const manual& manual);
    struct paper paper_;
    std::vector<instruction> instructions_;
};

auto parse(std::string_view input) -> manual;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day13

#endif
