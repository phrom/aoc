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
    auto file = read_file("../input/day4.txt");
    std::cout << "day4::part1 = " << day4::part1(file) << "\n";
    return 0;
}
