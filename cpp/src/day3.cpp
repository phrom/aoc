#include "day3.hpp"

#include <array>
#include <sstream>
#include <string>
#include <vector>

namespace day3 {

struct submarine
{
    submarine(std::vector<int> diagnostic_report, uint64_t bitsize)
        : diagnostic_report_{ std::move(diagnostic_report) }
        , bitsum_{}
        , bitsize_{ bitsize }
    {
        bitsum_.resize(bitsize_, 0);
        for (auto number : diagnostic_report_) {
            for (uint64_t i = 0; i < bitsize_; ++i) {
                bitsum_[i] += (number & (1 << i)) == 0 ? 0 : 1;
            }
        }
    }

    [[nodiscard]] auto gamma_rate() const -> int
    {
        int number = 0;
        for (uint64_t i = 0; i < bitsize_; ++i) {
            number |= most_common_bit(i) << i;
        }
        return number;
    }

    [[nodiscard]] auto epsilon_rate() const -> int
    {
        int number = 0;
        for (uint64_t i = 0; i < bitsize_; ++i) {
            number |= least_common_bit(i) << i;
        }
        return number;
    }

    [[nodiscard]] auto power_consumption() const -> int
    {
        return gamma_rate() * epsilon_rate();
    }

    [[nodiscard]] auto oxygen_generator_rating() const -> int
    {
        return select_by_bit_criteria(
            [b{ bitsize_ }](const auto& sub, int x, uint64_t pos) {
                uint64_t p = b - pos - 1;
                return (x & (1 << p)) != (sub.most_common_bit(p, 1) << p);
            });
    }

    [[nodiscard]] auto co2_scrubber_rating() -> int
    {
        return select_by_bit_criteria(
            [b{ bitsize_ }](const auto& sub, int x, uint64_t pos) {
                uint64_t p = b - pos - 1;
                return (x & (1 << p)) != (sub.least_common_bit(p, 0) << p);
            });
    }

    [[nodiscard]] auto life_support_rating() -> int
    {
        return oxygen_generator_rating() * co2_scrubber_rating();
    }

  private:
    [[nodiscard]] auto most_common_bit(uint64_t position, int def = 0) const
        -> int
    {
        double mid = static_cast<double>(diagnostic_report_.size()) / 2;
        if (bitsum_[position] > mid) {
            return 1;
        }
        if (bitsum_[position] == mid) {
            return def;
        }
        return 0;
    }

    [[nodiscard]] auto least_common_bit(uint64_t position, int def = 0) const
        -> int
    {
        double mid = static_cast<double>(diagnostic_report_.size()) / 2;
        if (bitsum_[position] > mid) {
            return 0;
        }
        if (bitsum_[position] == mid) {
            return def;
        }
        return 1;
    }

    [[nodiscard]] auto select_by_bit_criteria(
        auto bit_criteria,
        uint64_t position = 0) const -> int
    {
        std::vector<int> candidates = diagnostic_report_;
        candidates.erase(
            std::remove_if(
                candidates.begin(),
                candidates.end(),
                [&](int x) { return bit_criteria(*this, x, position); }),
            candidates.end());
        if (candidates.size() == 1 || position == bitsize_ - 1) {
            return candidates.front();
        }
        auto recur = submarine{ candidates, bitsize_ };
        return recur.select_by_bit_criteria(bit_criteria, position + 1);
    }

    std::vector<int> diagnostic_report_;
    std::vector<int> bitsum_;
    uint64_t bitsize_;
};

auto create_submarine(std::string_view input) -> submarine
{
    std::vector<int> diagnostic_report;
    std::istringstream iss{ std::string{ input } };
    std::string number_str;
    while (iss >> number_str) {
        int number = 0;
        for (uint64_t i = 0; i < number_str.size(); ++i) {
            number |= (number_str[i] - '0') << (number_str.size() - i - 1);
        }
        diagnostic_report.push_back(number);
    }
    return submarine{ diagnostic_report, number_str.size() };
}

auto part1(std::string_view input) -> int
{
    return create_submarine(input).power_consumption();
}

auto part2(std::string_view input) -> int
{
    return create_submarine(input).life_support_rating();
}

} // namespace day3
