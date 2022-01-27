#include "day14.hpp"

#include "print.hpp"

#include <algorithm>
#include <sstream>
#include <string>
#include <utility>

namespace day14 {
using ::operator<<;

element_count::element_count(char element, uint64_t count)
    : element_{ element }
    , count_{ count }
{}

auto element_count::get_element() const -> char
{
    return element_;
}

auto element_count::get_count() const -> uint64_t
{
    return count_;
}

auto element_count::operator<(const element_count& rhs) const -> bool
{
    return count_ < rhs.count_ ||
           (count_ == rhs.count_ && element_ < rhs.element_);
}

std::ostream& operator<<(std::ostream& out, const element_count& count)
{
    return out << "element_count { " << count.element_ << ", " << count.count_
               << "}";
}

pair_insertion_rule::pair_insertion_rule(symbol combination, char result)
    : combination_{ combination }
    , result_{ result }
{}

auto pair_insertion_rule::get_combination() const -> symbol
{
    return combination_;
}

auto pair_insertion_rule::get_result() const -> char
{
    return result_;
}

auto pair_insertion_rule::get_resulting_combinations() const
    -> std::array<symbol, 2>
{
    const auto make_symbol = [](char c1, char c2) {
        std::ostringstream oss;
        oss << c1 << c2;
        return symbol{ oss.str() };
    };

    const auto str = combination_.to_str();
    return { make_symbol(str[0], result_), make_symbol(result_, str[1]) };
}

std::ostream& operator<<(std::ostream& out, const pair_insertion_rule& rule)
{
    return out << "pair_insertion_rule { " << rule.combination_ << ", "
               << rule.result_ << "}";
}

polymer_template::polymer_template(std::string polymer)
    : symbol_count_{}
    , last_element_{ polymer.back() }
{
    for (uint64_t i = 0; i < polymer.size() - 1; ++i) {
        symbol_count_[symbol{ polymer.substr(i, 2) }]++;
    }
}

void polymer_template::insert_pairs(
    const std::vector<pair_insertion_rule>& rules)
{
    std::map<std::vector<pair_insertion_rule>::const_iterator, uint64_t>
        matched;
    for (const auto [symbol, count] : symbol_count_) {
        auto sym = symbol;
        if (const auto rit = std::find_if(
                rules.begin(),
                rules.end(),
                [=](const auto& rule) {
                    return rule.get_combination() == sym;
                });
            rit != rules.end()) {
            matched.insert({ rit, count });
        }
    }
    for (const auto [rit, count] : matched) {
        const auto c = rit->get_combination();
        symbol_count_[c] -= count;
        if (symbol_count_[c] == 0) {
            symbol_count_.erase(c);
        }
        for (const auto r : rit->get_resulting_combinations()) {
            symbol_count_[r] += count;
        }
    }
}

auto polymer_template::count_elements() const -> std::vector<element_count>
{
    std::map<char, uint64_t> count;
    for (auto [s, c] : symbol_count_) {
        count[s.to_str()[0]] += c;
    }
    count[last_element_]++;
    std::vector<element_count> result;
    result.reserve(count.size());
    for (auto [e, c] : count) {
        result.emplace_back(e, c);
    }
    std::sort(result.begin(), result.end());
    return result;
}

std::ostream& operator<<(std::ostream& out, const polymer_template& polymer_)
{
    return out << "polymer_template { " << polymer_.symbol_count_ << ", "
               << polymer_.last_element_ << " }";
}

manual::manual(polymer_template polymer, std::vector<pair_insertion_rule> rules)
    : polymer_{ std::move(polymer) }
    , rules_{ std::move(rules) }
{}

void manual::apply_steps(int n)
{
    for (int i = 0; i < n; ++i) {
        polymer_.insert_pairs(rules_);
    }
}

auto manual::count_elements() const -> std::vector<element_count>
{
    return polymer_.count_elements();
}

std::ostream& operator<<(std::ostream& out, const manual& manual)
{
    return out << "manual { " << manual.polymer_ << ", " << manual.rules_
               << "}";
}

auto parse(std::string_view input) -> manual
{
    std::vector<pair_insertion_rule> rules;
    std::istringstream iss{ std::string{ input } };
    std::string polymer;
    std::getline(iss, polymer);
    std::string line;
    std::getline(iss, line);
    while (std::getline(iss, line)) {
        std::istringstream lss{ line };
        std::string arrow;
        char combination1, combination2, result;
        lss >> combination1 >> combination2 >> arrow >> result;
        std::ostringstream combination;
        combination << combination1 << combination2;
        rules.emplace_back(symbol{ combination.str() }, result);
    }
    return { polymer_template{ std::move(polymer) }, rules };
}

auto part1(std::string_view input) -> uint64_t
{
    auto manual = parse(input);
    manual.apply_steps(10);
    const auto counts = manual.count_elements();
    if (counts.empty()) {
        return 0;
    }
    return counts.back().get_count() - counts.front().get_count();
}

auto part2(std::string_view input) -> uint64_t
{
    auto manual = parse(input);
    manual.apply_steps(40);
    const auto counts = manual.count_elements();
    if (counts.empty()) {
        return 0;
    }
    return counts.back().get_count() - counts.front().get_count();
}

} // namespace day14
