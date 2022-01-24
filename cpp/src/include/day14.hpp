#ifndef AOC_DAY14_HPP
#define AOC_DAY14_HPP

#include <map>
#include <string_view>
#include <vector>

#include "symbol.hpp"

namespace day14 {

struct element_count
{
    element_count(char element, uint64_t count);

    [[nodiscard]] auto get_element() const -> char;
    [[nodiscard]] auto get_count() const -> uint64_t;

    auto operator<(const element_count&) const -> bool;

  private:
    friend std::ostream& operator<<(std::ostream& out, const element_count&);
    char element_;
    uint64_t count_;
};

struct pair_insertion_rule
{
    pair_insertion_rule(symbol combination, char result);

    [[nodiscard]] auto get_combination() const -> symbol;
    [[nodiscard]] auto get_result() const -> char;
    [[nodiscard]] auto get_resulting_combinations() const
        -> std::array<symbol, 2>;

    auto operator==(const pair_insertion_rule&) const -> bool = default;

  private:
    friend std::ostream& operator<<(
        std::ostream& out,
        const pair_insertion_rule&);

    symbol combination_;
    char result_;
};

struct polymer_template
{
    explicit polymer_template(std::string polymer);

    void insert_pairs(const std::vector<pair_insertion_rule>&);
    [[nodiscard]] auto count_elements() const -> std::vector<element_count>;

    auto operator==(const polymer_template&) const -> bool = default;

  private:
    friend std::ostream& operator<<(std::ostream& out, const polymer_template&);
    std::map<symbol, uint64_t> symbol_count_;
    char last_element_;
};

struct manual
{
    manual(polymer_template polymer, std::vector<pair_insertion_rule> rules);

    void apply_steps(int n);
    [[nodiscard]] auto count_elements() const -> std::vector<element_count>;

    auto operator==(const manual&) const -> bool = default;

  private:
    friend std::ostream& operator<<(std::ostream& out, const manual&);

    polymer_template polymer_;
    std::vector<pair_insertion_rule> rules_;
};

auto parse(std::string_view input) -> manual;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day14

#endif
