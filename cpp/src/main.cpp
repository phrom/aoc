#include <fstream>
#include <iostream>

#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"
#include "day5.hpp"
#include "day6.hpp"

auto read_file(const char* filename) -> std::string
{
    std::ifstream file{ filename, std::fstream::in };
    return { std::istreambuf_iterator<char>{ file }, {} };
}

#define RUN(function, filename)                                                \
    std::cout << #function " = " << function(read_file("../input/" filename))  \
              << "\n"

auto main() -> int
{
    RUN(day1::part1, "day1.txt");
    RUN(day1::part2, "day1.txt");
    RUN(day2::part1, "day2.txt");
    RUN(day2::part2, "day2.txt");
    RUN(day3::part1, "day3.txt");
    RUN(day3::part2, "day3.txt");
    RUN(day4::part1, "day4.txt");
    RUN(day4::part2, "day4.txt");
    RUN(day5::part1, "day5.txt");
    RUN(day5::part2, "day5.txt");
    RUN(day6::part1, "day6.txt");
    RUN(day6::part2, "day6.txt");
    return 0;
}
