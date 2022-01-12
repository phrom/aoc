#include "day6.hpp"

#include <sstream>

namespace day6 {

school::school(std::vector<int> fish_)
    : fish{ std::move(fish_) }
{}

void school::advance_day()
{
    int add = 0;
    for (auto& f : fish) {
        if (f == 0) {
            f = 6;
            add++;
        } else {
            f--;
        }
    }
    while ((add--) != 0) {
        fish.push_back(8);
    }
}

auto parse(std::string_view input) -> school
{
    std::istringstream iss{ std::string{ input } };
    std::vector<int> fish;
    while (!iss.eof()) {
        int interval;
        char comma;
        iss >> interval >> comma;
        fish.push_back(interval);
    }
    return school{ fish };
}

auto part1(std::string_view input) -> int
{
    auto school = parse(input);
    const int date = 80;
    for (int i = 0; i < date; ++i) {
        school.advance_day();
    }
    return static_cast<int>(school.fish.size());
}

auto part2(std::string_view input) -> int
{
    return 0;
}

} // namespace day6
