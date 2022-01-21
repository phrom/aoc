#ifndef AOC_SYMBOL_HPP
#define AOC_SYMBOL_HPP

#include <compare>
#include <string>
#include <unordered_map>
#include <vector>

struct symbol
{
    explicit symbol(std::string string);

    [[nodiscard]] auto to_str() const -> std::string;

    auto operator<=>(const symbol&) const -> std::strong_ordering = default;

  private:
    uint64_t symbol_;
    static std::unordered_map<std::string, uint64_t> string_to_handle_;
    static std::vector<std::string_view> handle_to_string_;
};

std::ostream& operator<<(std::ostream&, const symbol&);

#endif
