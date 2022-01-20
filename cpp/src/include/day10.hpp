#ifndef AOC_DAY10_HPP
#define AOC_DAY10_HPP

#include <optional>
#include <stack>
#include <string>
#include <vector>

namespace day10 {

struct chunk
{
    explicit chunk(std::string chunk);

    [[nodiscard]] auto is_corrupted() const -> bool;
    [[nodiscard]] auto illegal_char() const -> std::optional<char>;
    [[nodiscard]] auto syntax_error_score() const -> int;

    [[nodiscard]] auto is_incomplete() const -> bool;
    [[nodiscard]] auto completion_string() const -> std::string;
    [[nodiscard]] auto completion_score() const -> uint64_t;

    auto operator==(const chunk&) const -> bool = default;

  private:
    std::string chunk_;
    std::stack<char> open_tokens_;
    std::optional<char> illegal_char_;
};

auto parse(std::string_view input) -> std::vector<chunk>;
auto part1(std::string_view input) -> int;
auto part2(std::string_view input) -> uint64_t;

} // namespace day10

#endif
