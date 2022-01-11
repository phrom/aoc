#include "day2.hpp"

#include <array>
#include <sstream>
#include <string>
#include <vector>

namespace day3 {

const int BITS_IN_DIAGNOSTIC_REPORT = 12;

struct submarine
{
    submarine(std::vector<int> diagnostic_report, int bitsize)
        : diagnostic_report_{ std::move(diagnostic_report) }
        , bitsize_{ bitsize }
    {
        bitsum_.resize(bitsize_, 0);
        for (auto number : diagnostic_report_) {
            for (int i = 0; i < bitsize_; ++i) {
                bitsum_[i] += (number & (1 << i)) == 0 ? 0 : 1;
            }
        }
    }

    [[nodiscard]] auto gamma_rate() const -> int
    {
        int number = 0;
        for (int i = 0; i < bitsize_; ++i) {
            number |= most_common_bit(i) << i;
        }
        return number;
    }

    [[nodiscard]] auto epsilon_rate() const -> int
    {
        int number = 0;
        for (int i = 0; i < bitsize_; ++i) {
            number |= least_common_bit(i) << i;
        }
        return number;
    }

    [[nodiscard]] auto power_consumption() const -> int
    {
        return gamma_rate() * epsilon_rate();
    }

  private:
    [[nodiscard]] auto most_common_bit(int position) const -> int
    {
        return bitsum_[position] > (diagnostic_report_.size() / 2) ? 1 : 0;
    }

    [[nodiscard]] auto least_common_bit(int position) const -> int
    {
        return most_common_bit(position) == 1 ? 0 : 1;
    }

    std::vector<int> diagnostic_report_;
    std::vector<int> bitsum_;
    int bitsize_;
};

auto part1(const char* input) -> int
{
    std::vector<int> diagnostic_report;
    std::istringstream iss{ input };
    std::string number_str;
    while (iss >> number_str) {
        int number = 0;
        for (int i = 0; i < number_str.size(); ++i) {
            number |= (number_str[i] - '0') << (number_str.size() - i - 1);
        }
        diagnostic_report.push_back(number);
    }
    submarine submarine{ diagnostic_report,
                         static_cast<int>(number_str.size()) };
    return submarine.power_consumption();
}

auto part2(const char* input) -> int
{
    return 0;
}

} // namespace day3
