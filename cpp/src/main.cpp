#include <fstream>
#include <iostream>

#include "day4.hpp"

auto read_file(const char* filename) -> std::string
{
    std::ifstream file{ filename, std::fstream::in };
    return { std::istreambuf_iterator<char>{ file }, {} };
}

auto main() -> int
{
    std::cout << "day4::part1 = " << day4::part1(read_file("../input/day4.txt"))
              << "\n";
    std::cout << "day4::part2 = " << day4::part2(read_file("../input/day4.txt"))
              << "\n";
    return 0;
}
