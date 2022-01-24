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
{
    for (int i = 0; i < polymer.size() - 1; ++i) {
        polymer_.emplace_back(polymer.substr(i, 2));
    }
}

void polymer_template::insert_pairs(
    const std::vector<pair_insertion_rule>& rules)
{
    for (auto it = polymer_.begin(); it != polymer_.end(); ++it) {
        if (auto rit = std::find_if(
                rules.begin(),
                rules.end(),
                [&](const auto& rule) {
                    return rule.get_combination() == *it;
                });
            rit != rules.end()) {
            it = polymer_.erase(it);
            auto [f, s] = rit->get_resulting_combinations();
            it = polymer_.emplace(it, f);
            it = polymer_.emplace(++it, s);
        }
    }
}

auto polymer_template::count_elements() const -> std::vector<element_count>
{
    std::map<char, int> count;
    for (symbol s : polymer_) {
        char c = s.to_str()[0];
        auto it = count.find(c);
        if (it == count.end()) {
            it = count.insert(it, { c, 0 });
        }
        it->second++;
    }
    char c = polymer_.back().to_str()[1];
    auto it = count.find(c);
    if (it == count.end()) {
        it = count.insert(it, { c, 0 });
    }
    it->second++;
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
    return out << "polymer_template { " << polymer_.polymer_ << "}";
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
    std::cout << "counts: " << counts << "\n";
    if (counts.empty()) {
        return 0;
    }
    return counts.back().get_count() - counts.front().get_count();
}

auto part2(std::string_view input) -> uint64_t
{
    auto manual = parse(input);
    manual.apply_steps(20);
    const auto counts = manual.count_elements();
    if (counts.empty()) {
        return 0;
    }
    return counts.back().get_count() - counts.front().get_count();
}

} // namespace day14
