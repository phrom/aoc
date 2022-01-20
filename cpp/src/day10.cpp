#include "day10.hpp"

#include <numeric>
#include <sstream>
#include <stack>
#include <string>

namespace day10 {

chunk::chunk(std::string chunk)
    : chunk_{ std::move(chunk) }
{}

auto chunk::is_corrupted() const -> bool
{
    return illegal_char().has_value();
}

auto chunk::illegal_char() const -> std::optional<char>
{
    std::stack<char> open_tokens;
    for (char c : chunk_) {
        switch (c) {
            case '(':
            case '[':
            case '{':
            case '<':
                open_tokens.push(c);
                break;
            case ')':
                if (open_tokens.top() == '(') {
                    open_tokens.pop();
                } else {
                    return c;
                }
                break;
            case ']':
                if (open_tokens.top() == '[') {
                    open_tokens.pop();
                } else {
                    return c;
                }
                break;
            case '}':
                if (open_tokens.top() == '{') {
                    open_tokens.pop();
                } else {
                    return c;
                }
                break;
            case '>':
                if (open_tokens.top() == '<') {
                    open_tokens.pop();
                } else {
                    return c;
                }
                break;
        }
    }
    return {};
}

auto chunk::syntax_error_score() const -> int
{
    if (auto ch = illegal_char()) {
        switch (*ch) {
            case ')':
                return 3;
            case ']':
                return 57;
            case '}':
                return 1197;
            case '>':
                return 25137;
        }
    }
    return 0;
}

auto parse(std::string_view input) -> std::vector<chunk>
{
    std::vector<chunk> result;
    std::istringstream iss{ std::string{ input } };
    std::string line;
    while (std::getline(iss, line)) {
        result.emplace_back(line);
    }
    return result;
}

auto part1(std::string_view input) -> int
{
    const auto chunks = parse(input);
    return std::accumulate(
        chunks.begin(), chunks.end(), 0, [](int total, const auto& chunk) {
            return total + chunk.syntax_error_score();
        });
    return 0;
}

auto part2(std::string_view input) -> int
{
    return 0;
}

} // namespace day10
