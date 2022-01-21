#include <fstream>
#include <iostream>

#include "day1.hpp"
#include "day10.hpp"
#include "day11.hpp"
#include "day12.hpp"
#include "day13.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"
#include "day5.hpp"
#include "day6.hpp"
#include "day7.hpp"
#include "day8.hpp"
#include "day9.hpp"

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
    RUN(day7::part1, "day7.txt");
    RUN(day7::part2, "day7.txt");
    RUN(day8::part1, "day8.txt");
    RUN(day8::part2, "day8.txt");
    RUN(day9::part1, "day9.txt");
    RUN(day9::part2, "day9.txt");
    RUN(day10::part1, "day10.txt");
    RUN(day10::part2, "day10.txt");
    RUN(day11::part1, "day11.txt");
    RUN(day11::part2, "day11.txt");
    RUN(day12::part1, "day12.txt");
    RUN(day12::part2, "day12.txt");
    RUN(day13::part1, "day13.txt");
    RUN(day13::part2, "day13.txt");
    return 0;
}
