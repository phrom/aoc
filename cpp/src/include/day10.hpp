#ifndef AOC_DAY10_HPP
#define AOC_DAY10_HPP

#include <optional>
#include <string>
#include <vector>

namespace day10 {

struct chunk
{
    explicit chunk(std::string chunk);

    [[nodiscard]] auto is_corrupted() const -> bool;
    [[nodiscard]] auto illegal_char() const -> std::optional<char>;
    [[nodiscard]] auto syntax_error_score() const -> int;

    auto operator==(const chunk&) const -> bool = default;

  private:
    std::string chunk_;
};

auto parse(std::string_view input) -> std::vector<chunk>;
auto part1(std::string_view input) -> int;
auto part2(std::string_view input) -> int;

} // namespace day10

#endif
