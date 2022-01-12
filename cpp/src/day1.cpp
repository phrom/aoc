#include "day1.hpp"

#include <sstream>
#include <string>
#include <vector>

namespace day1 {

auto part1(std::string_view input) -> int
{
    std::istringstream iss{ std::string{ input } };
    int prev = 0;
    int next = 0;
    int count = -1;
    while (iss >> next) {
        if (next > prev) {
            count += 1;
        }
        prev = next;
    }
    return count;
}

auto part2(std::string_view input) -> int
{
    auto numbers = [&]() {
        std::vector<int> result;
        std::istringstream iss{ std::string{ input } };
        int number;
        while (iss >> number) {
            result.push_back(number);
        }
        return result;
    }();

    int prev = 0;
    int next = 0;
    int count = -1;
    for (int i = 0; i < numbers.size() - 2; ++i) {
        next = numbers[i] + numbers[i + 1] + numbers[i + 2];
        if (next > prev) {
            count += 1;
        }
        prev = next;
    }
    return count;
}

} // namespace day1
