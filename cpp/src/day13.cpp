#include "day13.hpp"

#include "print.hpp"

#include <sstream>
#include <string>

namespace day13 {
using ::operator<<;

paper::paper(matrix<bool> paper)
    : paper_{ std::move(paper) }
{}

void paper::fold(const struct instruction& instruction)
{
    if (instruction.get_axis() == instruction::axis::x) {
        for (int i = 0; i < paper_.rows(); ++i) {
            for (int j = instruction.get_coord(); j < paper_.columns(i); ++j) {
                if (paper_.get(i, j)) {
                    paper_.set(i, 2 * instruction.get_coord() - j, true);
                }
            }
        }
        paper_.remove_columns(instruction.get_coord());
    }
    if (instruction.get_axis() == instruction::axis::y) {
        for (int i = instruction.get_coord(); i < paper_.rows(); ++i) {
            for (int j = 0; j < paper_.columns(i); ++j) {
                if (paper_.get(i, j)) {
                    paper_.set(2 * instruction.get_coord() - i, j, true);
                }
            }
        }
        paper_.remove_rows(instruction.get_coord());
    }
}

auto paper::visible_dots() const -> std::vector<std::pair<int, int>>
{
    std::vector<std::pair<int, int>> result;
    for (int i = 0; i < paper_.rows(); ++i) {
        for (int j = 0; j < paper_.columns(i); ++j) {
            if (paper_.get(i, j)) {
                result.emplace_back(i, j);
            }
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const paper& paper)
{
    return out << "paper {\n" << paper.paper_ << "\n}";
}

instruction::instruction(axis axis, int coord)
    : axis_{ axis }
    , coord_{ coord }
{}

auto instruction::get_axis() const -> axis
{
    return axis_;
}

auto instruction::get_coord() const -> int
{
    return coord_;
}

std::ostream& operator<<(std::ostream& out, const instruction::axis& axis)
{
    switch (axis) {
        case instruction::axis::x:
            return out << "x";
        case instruction::axis::y:
            return out << "y";
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const instruction& instruction)
{
    return out << "instruction { " << instruction.axis_ << ", "
               << instruction.coord_ << " }";
}

manual::manual(paper paper, std::vector<instruction> instructions)
    : paper_{ std::move(paper) }
    , instructions_{ std::move(instructions) }
{}

auto manual::get_paper() -> paper&
{
    return paper_;
}

auto manual::get_instructions() const -> const std::vector<instruction>&
{
    return instructions_;
}

std::ostream& operator<<(std::ostream& out, const manual& manual)
{
    return out << "manual { " << manual.paper_ << ", " << manual.instructions_
               << " }";
}

auto parse(std::string_view input) -> manual
{
    matrix<bool> paper;
    std::vector<instruction> instructions;
    std::istringstream iss{ std::string{ input } };
    std::string line;
    while (std::getline(iss, line)) {
        if (line.empty()) {
            break;
        }
        std::istringstream lss{ line };
        int x, y;
        char comma;
        lss >> x >> comma >> y;
        paper.set(y, x, true);
    }
    while (std::getline(iss, line)) {
        std::istringstream lss{ line };
        std::string fold, along;
        char axis, equal;
        int coord;
        lss >> fold >> along >> axis >> equal >> coord;
        instructions.emplace_back(
            axis == 'x' ? instruction::axis::x : instruction::axis::y, coord);
    }
    return manual{ day13::paper{ std::move(paper) }, std::move(instructions) };
}

auto part1(std::string_view input) -> uint64_t
{
    auto manual = parse(input);
    auto& paper = manual.get_paper();
    paper.fold(manual.get_instructions().front());
    return paper.visible_dots().size();
}

auto part2(std::string_view input) -> uint64_t
{
    auto manual = parse(input);
    auto& paper = manual.get_paper();
    for (const auto& instruction : manual.get_instructions()) {
        paper.fold(instruction);
    }
    std::cout << paper;
    return 42;
}

} // namespace day13
