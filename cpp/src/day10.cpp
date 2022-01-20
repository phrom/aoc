#include "day10.hpp"

#include <numeric>
#include <sstream>
#include <stack>
#include <string>

namespace day10 {

chunk::chunk(std::string chunk)
    : chunk_{ std::move(chunk) }
{
    for (char c : chunk_) {
        switch (c) {
            case '(':
            case '[':
            case '{':
            case '<':
                open_tokens_.push(c);
                break;
            case ')':
                if (open_tokens_.top() == '(') {
                    open_tokens_.pop();
                } else {
                    illegal_char_ = c;
                    return;
                }
                break;
            case ']':
                if (open_tokens_.top() == '[') {
                    open_tokens_.pop();
                } else {
                    illegal_char_ = c;
                    return;
                }
                break;
            case '}':
                if (open_tokens_.top() == '{') {
                    open_tokens_.pop();
                } else {
                    illegal_char_ = c;
                    return;
                }
                break;
            case '>':
                if (open_tokens_.top() == '<') {
                    open_tokens_.pop();
                } else {
                    illegal_char_ = c;
                    return;
                }
                break;
        }
    }
}

auto chunk::is_corrupted() const -> bool
{
    return illegal_char().has_value();
}

auto chunk::illegal_char() const -> std::optional<char>
{
    return illegal_char_;
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

auto chunk::is_incomplete() const -> bool
{
    return !is_corrupted() && !completion_string().empty();
}

auto chunk::completion_string() const -> std::string
{
    std::stack tokens = open_tokens_;
    std::ostringstream completion;
    while (!tokens.empty()) {
        switch (tokens.top()) {
            case '(':
                completion << ')';
                break;
            case '[':
                completion << ']';
                break;
            case '{':
                completion << '}';
                break;
            case '<':
                completion << '>';
                break;
        }
        tokens.pop();
    }
    return completion.str();
}

auto chunk::completion_score() const -> uint64_t
{
    uint64_t total = 0;
    for (char c : completion_string()) {
        total *= 5;
        switch (c) {
            case ')':
                total += 1;
                break;
            case ']':
                total += 2;
                break;
            case '}':
                total += 3;
                break;
            case '>':
                total += 4;
                break;
        }
    }
    return total;
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
}

auto part2(std::string_view input) -> uint64_t
{
    const auto chunks = parse(input);
    std::vector<uint64_t> scores;
    for (const auto& chunk : chunks) {
        if (chunk.is_incomplete()) {
            const auto score = chunk.completion_score();
            scores.insert(
                std::lower_bound(scores.begin(), scores.end(), score), score);
        }
    }
    return scores[scores.size() / 2];
}

} // namespace day10
