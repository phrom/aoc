#include "day8.hpp"

#include <algorithm>
#include <numeric>
#include <sstream>
#include <string>

namespace day8 {

display::display(
    std::vector<std::string> input_signals,
    std::vector<std::string> output_signals)
    : input_signals_{ std::move(input_signals) }
    , output_signals_{ std::move(output_signals) }
{}

auto signal_difference(const std::string& s1, const std::vector<char>& s2)
    -> char
{
    for (char c1 : s1) {
        if (std::find(s2.begin(), s2.end(), c1) == s2.end()) {
            return c1;
        }
    }
    return 0;
};

auto signal_intersection(const std::vector<std::string>& set) -> std::string
{
    if (!set.empty()) {
        std::ostringstream oss;
        for (char c1 : set[0]) {
            if (std::all_of(set.begin() + 1, set.end(), [=](const auto& s) {
                    return std::find(s.begin(), s.end(), c1) != s.end();
                })) {
                oss << c1;
            }
        }
        return oss.str();
    }
    return {};
};

auto build_string(const std::vector<char>& chars) -> std::string
{
    std::ostringstream oss;
    for (char c : chars) {
        oss << c;
    }
    std::string result = oss.str();
    std::sort(result.begin(), result.end());
    return result;
};

auto display::outputs() const -> std::vector<int>
{
    std::string one, four, seven, eight;
    std::vector<std::string> five_signals, six_signals;
    for (const auto& s : input_signals_) {
        switch (s.size()) {
            case 2:
                one = s;
                break;
            case 3:
                seven = s;
                break;
            case 4:
                four = s;
                break;
            case 5:
                five_signals.push_back(s);
                break;
            case 6:
                six_signals.push_back(s);
                break;
            case 7:
                eight = s;
                break;
        }
    }

    std::vector<char> one_vec;
    for (char c : one) {
        one_vec.push_back(c);
    }
    const char a = signal_difference(seven, one_vec);
    const std::string abfg = signal_intersection(six_signals);
    const char f = signal_intersection({ abfg, one })[0];
    const char c = signal_difference(one, std::vector{ f });
    const std::string bf = signal_intersection({ four, abfg });
    const char b = signal_difference(bf, std::vector{ f });
    const char g = signal_difference(
        signal_intersection(six_signals), std::vector{ a, b, f });
    const char d = signal_difference(
        signal_intersection(five_signals), std::vector{ a, g });
    const char e = signal_difference(eight, std::vector{ a, b, c, d, f, g });

    const std::string zero = build_string({ a, b, c, e, f, g });
    std::sort(one.begin(), one.end());
    const std::string two = build_string({ a, c, d, e, g });
    const std::string three = build_string({ a, c, d, f, g });
    std::sort(four.begin(), four.end());
    const std::string five = build_string({ a, b, d, f, g });
    const std::string six = build_string({ a, b, d, e, f, g });
    std::sort(seven.begin(), seven.end());
    std::sort(eight.begin(), eight.end());
    const std::string nine = build_string({ a, b, c, d, f, g });

    std::vector<int> result;
    result.reserve(output_signals_.size());
    for (const auto& s : output_signals_) {
        std::string sorted = s;
        std::sort(sorted.begin(), sorted.end());
        if (sorted == zero) {
            result.push_back(0);
        } else if (sorted == one) {
            result.push_back(1);
        } else if (sorted == two) {
            result.push_back(2);
        } else if (sorted == three) {
            result.push_back(3);
        } else if (sorted == four) {
            result.push_back(4);
        } else if (sorted == five) {
            result.push_back(5);
        } else if (sorted == six) {
            result.push_back(6);
        } else if (sorted == seven) {
            result.push_back(7);
        } else if (sorted == eight) {
            result.push_back(8);
        } else if (sorted == nine) {
            result.push_back(9);
        }
    }
    return result;
}

auto parse(std::string_view input) -> std::vector<display>
{
    std::vector<display> result;
    std::istringstream iss{ std::string{ input } };
    std::string line;
    while (std::getline(iss, line)) {
        std::istringstream lss{ line };
        bool input = true;
        std::vector<std::string> inputs;
        std::vector<std::string> outputs;
        while (lss.good()) {
            std::string code;
            lss >> code;
            if (code == "|") {
                input = false;
                continue;
            }
            if (input) {
                inputs.push_back(code);
            } else {
                outputs.push_back(code);
            }
        }
        result.emplace_back(inputs, outputs);
    }
    return result;
}

auto part1(std::string_view input) -> int
{
    const auto displays = parse(input);
    return std::accumulate(
        displays.begin(),
        displays.end(),
        0,
        [](int result, const display& display) {
            const auto outputs = display.outputs();
            return result +
                   std::count_if(outputs.begin(), outputs.end(), [](int x) {
                       return x == 1 || x == 4 || x == 7 || x == 8;
                   });
        });
}

auto part2(std::string_view input) -> int
{
    const auto displays = parse(input);
    return std::accumulate(
        displays.begin(),
        displays.end(),
        0,
        [](int total, const auto& display) {
            const auto outputs = display.outputs();
            return total + outputs[0] * 1000 + outputs[1] * 100 +
                   outputs[2] * 10 + outputs[3];
        });
}

} // namespace day8
