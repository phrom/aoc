#include "read_file.hpp"

#include <fstream>

auto read_file(const char* filename) -> std::string
{
    std::ifstream file{ std::string{ INPUT_FOLDER } + "/" + filename,
                        std::fstream::in };
    return { std::istreambuf_iterator<char>{ file }, {} };
}
