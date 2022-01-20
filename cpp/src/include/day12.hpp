#ifndef AOC_DAY12_HPP
#define AOC_DAY12_HPP

#include <map>
#include <set>
#include <string>
#include <vector>

namespace day12 {

struct cave
{
    explicit cave(std::string name);

    void add_connection(const std::string& destination);

    [[nodiscard]] auto name() const -> std::string;
    [[nodiscard]] auto is_big_cave() const -> bool;
    [[nodiscard]] auto is_small_cave() const -> bool;
    [[nodiscard]] auto connected_caves() const -> const std::set<std::string>&;

    auto operator==(const cave&) const -> bool = default;

  private:
    friend std::ostream& operator<<(std::ostream& out, const cave& cave);
    std::string name_;
    std::set<std::string> connected_caves_;
};

struct path
{
    explicit path(std::vector<std::string> path);

    [[nodiscard]] auto contains(const std::string&) const -> bool;
    void add(const std::string&);

  private:
    friend std::ostream& operator<<(std::ostream& out, const path& path);
    std::vector<std::string> path_;
};

struct cave_system
{
    void add_connection(const std::string& from, const std::string& to);

    [[nodiscard]] auto paths(bool revisit = false) const -> std::vector<path>;
    auto operator==(const cave_system&) const -> bool = default;

  private:
    void find_paths(
        std::vector<path>& all,
        path& current,
        const cave& cave,
        bool revisit) const;
    friend std::ostream& operator<<(std::ostream& out, const cave_system& cave);
    std::map<std::string, cave> caves_;
};

auto parse(std::string_view input) -> cave_system;
auto part1(std::string_view input) -> uint64_t;
auto part2(std::string_view input) -> uint64_t;

} // namespace day12

#endif
