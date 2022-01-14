#ifndef AOC_DAY8_HPP
#define AOC_DAY8_HPP

#include <string>
#include <string_view>
#include <vector>

namespace day8 {

struct display
{
    display(
        std::vector<std::string> input_signals,
        std::vector<std::string> output_signals);

    [[nodiscard]] auto outputs() const -> std::vector<int>;

  private:
    std::vector<std::string> input_signals_;
    std::vector<std::string> output_signals_;
};

auto signal_difference(const std::string& s1, const std::vector<char>& s2)
    -> char;
auto signal_intersection(const std::vector<std::string>& set) -> std::string;
auto build_string(const std::vector<char>& chars) -> std::string;

auto parse(std::string_view input) -> std::vector<display>;
auto part1(std::string_view input) -> int;
auto part2(std::string_view input) -> int;

} // namespace day8

#endif
