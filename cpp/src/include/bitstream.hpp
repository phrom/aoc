#ifndef AOC_BITSTREAM_HPP
#define AOC_BITSTREAM_HPP

#include <string>

struct bitstream
{
    explicit bitstream(std::string input);

    [[nodiscard]] auto read(uint64_t bits) -> uint64_t;

    static auto bitmask(uint64_t bits) -> uint64_t;

  private:
    std::string input_;
    uint64_t char_;
    uint64_t bit_;
};

#endif
