#include <fstream>
#include <iostream>

#include "day4.hpp"
#include "day5.hpp"

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
    RUN(day4::part1, "day4.txt");
    RUN(day4::part2, "day4.txt");
    RUN(day5::part1, "day5.txt");
    RUN(day5::part2, "day5.txt");
    return 0;
}
