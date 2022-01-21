#ifndef AOC_DAY12_HPP
#define AOC_DAY12_HPP

#include "symbol.hpp"

#include <map>
#include <set>
#include <string_view>
#include <vector>

namespace day12 {

struct cave
{
    explicit cave(symbol name);

    void add_connection(symbol destination);

    [[nodiscard]] auto name() const -> symbol;
    [[nodiscard]] auto is_big_cave() const -> bool;
    [[nodiscard]] auto is_small_cave() const -> bool;
    [[nodiscard]] auto connected_caves() const -> const std::set<symbol>&;

    auto operator==(const cave&) const -> bool = default;

  private:
    friend std::ostream& operator<<(std::ostream& out, const cave& cave);
    symbol name_;
    std::set<symbol> connected_caves_;
};

struct path
{
    explicit path(std::vector<symbol> path);

    [[nodiscard]] auto contains(symbol) const -> bool;
    void add(symbol);

  private:
    friend std::ostream& operator<<(std::ostream& out, const path& path);
    std::vector<symbol> path_;
};

struct cave_system
{
    void add_connection(symbol from, symbol to);

    [[nodiscard]] auto paths(bool revisit = false) const -> std::vector<path>;
    auto operator==(const cave_system&) const -> bool = default;

  private:
    void find_paths(
        std::vector<path>& all,
        path& current,
        const cave& cave,
        bool revisit) const;
    friend std::ostream& operator<<(std::ostream& out, const cave_system& cave);
    std::map<symbol, cave> caves_;
};

auto parse(std::string_view input) -> cave_system;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day12

#endif
